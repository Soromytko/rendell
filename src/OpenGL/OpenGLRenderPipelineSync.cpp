#include <OpenGL/OpenGLRenderPipelineSync.h>

#include <OpenGL/OpenGLResourceStorage.h>
#include <RendellExtractor.h>
#include <RenderCommandBufferImpl.h>
#include <ResourceCommandBufferImpl.h>
#include <context_creation.h>
#include <rendell/RenderCommandBuffer.h>
#include <rendell/ResourceCommandBuffer.h>

namespace rendell {
OpenGLRenderPipelineSync::OpenGLRenderPipelineSync(NativeView nativeView, Callbacks callbacks)
    : RenderPipeline(callbacks) {
    _context = createOpenGLContext(nativeView);
}

OpenGLRenderPipelineSync::~OpenGLRenderPipelineSync() {
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

void OpenGLRenderPipelineSync::submitResourceContext(ResourceCommandBuffer *buffer) {
    _resourceCommandBuffers.push(buffer);
}

void OpenGLRenderPipelineSync::submitRenderContext(RenderCommandBuffer *buffer) {
    _renderCommandBuffers.push(buffer);
}

void OpenGLRenderPipelineSync::waitAndRender() {
    _resourceExecutor.resetReleasedResourceIds();
    render();
}

void OpenGLRenderPipelineSync::render() {
    // Execute ResourceContext
    {
        while (!_resourceCommandBuffers.isEmpty()) {
            auto resourceCommandBuffer = _resourceCommandBuffers.pop();
            assert(resourceCommandBuffer);

            ResourceCommandBufferImpl &impl = RendellExtractor::extractImpl(*resourceCommandBuffer);
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
}

} // namespace rendell