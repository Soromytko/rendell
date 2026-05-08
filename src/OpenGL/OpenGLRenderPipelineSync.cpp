#include <OpenGL/OpenGLRenderPipelineSync.h>

#include <OpenGL/OpenGLResourceStorage.h>
#include <RenderContext.h>
#include <ResourceContext.h>
#include <context_creation.h>

namespace rendell {
OpenGLRenderPipelineSync::OpenGLRenderPipelineSync(NativeView nativeView) {
    _context = createOpenGLContext(nativeView);
}

OpenGLRenderPipelineSync::~OpenGLRenderPipelineSync() {
    releaseOpenGLResourceStorages();
    _context.reset();
}

bool OpenGLRenderPipelineSync::isInitialized() const {
    return _context && _context->isInitialized();
}

const IContext *OpenGLRenderPipelineSync::getContext() const {
    return _context.get();
}

void OpenGLRenderPipelineSync::run() {
    assert(_context);
    assert(_context->isInitialized());
    _context->makeCurrent();
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
}

void OpenGLRenderPipelineSync::submitResourceContext(
    std::unique_ptr<ResourceContext> resourceContext) {
    _resourceContextBuffer.push(std::move(resourceContext));
}

void OpenGLRenderPipelineSync::submitRenderContext(std::unique_ptr<RenderContext> renderContext) {
    _renderContextBuffer.push(std::move(renderContext));
}

void OpenGLRenderPipelineSync::waitAndRender() {
    render();
}

void OpenGLRenderPipelineSync::render() {
    // Execute ResourceContext.
    while (!_resourceContextBuffer.isEmpty()) {
        auto resourceContext = _resourceContextBuffer.pop();
        assert(resourceContext);

        const ByteBuffer &commandBuffer = resourceContext->getCommandBuffer();
        ResourceDataProviderSharedPtr dataProvider = resourceContext->getResourceDataProvider();
        assert(dataProvider);
        _resourceExecutor.execute(commandBuffer, dataProvider);

        resourceContext->reset();
        _resourceContextReleasedCallback(std::move(resourceContext));
    }

    // Execute RenderContext.
    while (!_renderContextBuffer.isEmpty()) {
        auto renderContext = _renderContextBuffer.pop();
        assert(renderContext);

        const DrawCallStateList &drawCallStateList = renderContext->getDrawCallStateList();
        const ByteBuffer &uniformBuffer = renderContext->getUniformBuffer();
        const ByteBuffer &commandBuffer = renderContext->getCommandBuffer();

        _renderExecutor.execute(drawCallStateList, uniformBuffer, commandBuffer);

        renderContext->reset();
        _renderContextReleasedCallback(std::move(renderContext));
    }
    _context->swapBuffers();
}

} // namespace rendell