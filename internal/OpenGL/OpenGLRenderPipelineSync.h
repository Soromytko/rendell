#pragma once
#include <RenderPipeline.h>

#include "OpenGLContext.h"
#include "OpenGLRenderExecutor.h"
#include "OpenGLResourceExecutor.h"
#include <Buffers/RingBuffer.h>
#include <rendell/init_types.h>

namespace rendell {
class OpenGLRenderPipelineSync final : public RenderPipeline {
public:
    OpenGLRenderPipelineSync(NativeView nativeView, Callbacks callbacks);
    ~OpenGLRenderPipelineSync();

    bool isInitialized() const override;
    const IContext *getContext() const override;

    const ReleasedResourceIds &getReleasedResourceIds() const override {
        return _resourceExecutor.getReleasedResourceIds();
    }

    void run() override;

    void submitResourceContext(ResourceCommandBuffer *buffer) override;
    void submitRenderContext(RenderCommandBuffer *buffer) override;

    void waitAndRender() override;

private:
    void render();

    OpenGLContextUniquePtr _context;
    OpenGLResourceExecutor _resourceExecutor;
    OpenGLRenderExecutor _renderExecutor;

    RingBuffer<ResourceCommandBuffer *> _resourceCommandBuffers;
    RingBuffer<RenderCommandBuffer *> _renderCommandBuffers;
};
} // namespace rendell