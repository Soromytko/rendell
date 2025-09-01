#include <OpenGL/OpenGLRenderPipeline.h>

#include <OpenGL/OpenGLResourceStorage.h>
#include <RenderContext.h>
#include <ResourceContext.h>
#include <context_creation.h>

namespace rendell {
OpenGLRenderPipeline::OpenGLRenderPipeline(NativeView nativeView) {
    _context = createOpenGLContext(nativeView);
}

OpenGLRenderPipeline::~OpenGLRenderPipeline() {
    {
        std::lock_guard<std::mutex> lock(_renderingMutex);
        _running = false;
        _renderThreadCV.notify_one();
    }
    if (_renderThread.joinable()) {
        _renderThread.join();
    }

    releaseOpenGLResourceStorages();
    _context.reset();
}

bool OpenGLRenderPipeline::isInitialized() const {
    return _context && _context->isInitialized();
}

const IContext *OpenGLRenderPipeline::getContext() const {
    return _context.get();
}

void OpenGLRenderPipeline::run() {
    assert(!_running);
    assert(_context);
    assert(_context->isInitialized());
    _context->makeUncurrent();
    _running = true;
    _renderThread = std::thread(&OpenGLRenderPipeline::rendering, this);
}

void OpenGLRenderPipeline::submitResourceContext(ResourceContext *resourceContext) {
    std::lock_guard<std::mutex> lock(_renderingMutex);
    _resourceContextBuffer.push(resourceContext);
}

void OpenGLRenderPipeline::submitRenderContext(RenderContext *renderContext) {
    std::lock_guard<std::mutex> lock(_renderingMutex);
    _renderContextBuffer.push(renderContext);
}

void OpenGLRenderPipeline::waitAndRender() {
    std::lock_guard<std::mutex> lock(_renderingMutex);
    _hasRenderTask = !_resourceContextBuffer.isEmpty() || !_renderContextBuffer.isEmpty();
    if (_hasRenderTask) {
        _renderThreadCV.notify_one();
    }
}

void OpenGLRenderPipeline::rendering() {
    _context->makeCurrent();
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    while (waitForRenderTask()) {
        std::lock_guard<std::mutex> lock(_renderingMutex);

        // Execute ResourceContext
        {
            while (!_resourceContextBuffer.isEmpty()) {
                ResourceContext *resourceContext = _resourceContextBuffer.pop();
                assert(resourceContext);

                const ByteBuffer &commandBuffer = resourceContext->getCommandBuffer();
                ResourceDataProviderSharedPtr dataProvider =
                    resourceContext->getResourceDataProvider();
                assert(dataProvider);
                _resourceExecutor.execute(commandBuffer, dataProvider);

                resourceContext->reset();
                _resourceContextReleasedCallback(resourceContext);
            }
        }

        // Execute RenderContext.
        {
            while (!_renderContextBuffer.isEmpty()) {
                RenderContext *renderContext = _renderContextBuffer.pop();
                assert(renderContext);

                const DrawCallStateList &drawCallStateList = renderContext->getDrawCallStateList();
                const ByteBuffer &uniformBuffer = renderContext->getUniformBuffer();
                const ByteBuffer &commandBuffer = renderContext->getCommandBuffer();

                _renderExecutor.execute(drawCallStateList, uniformBuffer, commandBuffer);

                renderContext->reset();
                _renderContextReleasedCallback(renderContext);
            }
            _context->swapBuffers();
        }

        _hasRenderTask = false;
    }

    _context->makeUncurrent();
}

bool OpenGLRenderPipeline::waitForRenderTask() {
    std::unique_lock<std::mutex> lock(_renderingMutex);
    _renderThreadCV.wait(lock, [&] { return _hasRenderTask || !_running; });
    return _running;
}
} // namespace rendell