#include <OpenGL/OpenGLRenderPipeline.h>

#include <OpenGL/OpenGLResourceStorage.h>
#include <RendellExtractor.h>
#include <RenderCommandBufferImpl.h>
#include <ResourceCommandBufferImpl.h>
#include <context_creation.h>
#include <rendell/RenderCommandBuffer.h>
#include <rendell/ResourceCommandBuffer.h>

namespace rendell {
OpenGLRenderPipeline::OpenGLRenderPipeline(NativeView nativeView, Callbacks callbacks)
    : RenderPipeline(callbacks) {
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

    // Return buffers
    {
        while (!_resourceCommandBuffers.isEmpty()) {
            _callbacks.returnResourceCommandBuffer(_resourceCommandBuffers.pop());
        }
        while (!_renderCommandBuffers.isEmpty()) {
            _callbacks.returnRenderCommandBuffer(_renderCommandBuffers.pop());
        }
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

void OpenGLRenderPipeline::submitResourceContext(ResourceCommandBuffer *buffer) {
    std::lock_guard<std::mutex> lock(_renderingMutex);
    _resourceCommandBuffers.push(buffer);
}

void OpenGLRenderPipeline::submitRenderContext(RenderCommandBuffer *buffer) {
    std::lock_guard<std::mutex> lock(_renderingMutex);
    _renderCommandBuffers.push(buffer);
}

void OpenGLRenderPipeline::waitAndRender() {
    std::lock_guard<std::mutex> lock(_renderingMutex);
    _resourceExecutor.resetReleasedResourceIds();
    _hasRenderTask = !_resourceCommandBuffers.isEmpty() || !_renderCommandBuffers.isEmpty();
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
            while (!_resourceCommandBuffers.isEmpty()) {
                auto resourceCommandBuffer = _resourceCommandBuffers.pop();
                assert(resourceCommandBuffer);

                ResourceCommandBufferImpl &impl =
                    RendellExtractor::extractImpl(*resourceCommandBuffer);
                const ByteBuffer &commandBuffer = impl.resourceCommandBuffer;
                ResourceDataProvider &dataProvider = impl.resourceDataProvider;
                _resourceExecutor.execute(commandBuffer, dataProvider);

                impl.reset();
                _callbacks.returnResourceCommandBuffer(resourceCommandBuffer);
            }
        }

        // Execute RenderContext.
        {
            while (!_renderCommandBuffers.isEmpty()) {
                auto renderCommandBuffer = _renderCommandBuffers.pop();
                assert(renderCommandBuffer);

                RenderCommandBufferImpl &impl = RendellExtractor::extractImpl(*renderCommandBuffer);

                const DrawCallStateList &drawCallStateList = impl.drawCallStates;
                const ByteBuffer &uniformBuffer = impl.uniformBuffer;
                const ByteBuffer &commandBuffer = impl.commandBuffer;

                _renderExecutor.execute(drawCallStateList, uniformBuffer, commandBuffer);

                impl.reset();
                _callbacks.returnRenderCommandBuffer(renderCommandBuffer);
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