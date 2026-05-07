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
    OpenGLRenderPipelineSync(NativeView nativeView);
    ~OpenGLRenderPipelineSync();

    bool isInitialized() const override;
    const IContext *getContext() const override;

    void run() override;

    void submitResourceContext(ResourceContext *resourceContext) override;
    void submitRenderContext(RenderContext *renderContext) override;

    void waitAndRender() override;

private:
    void render();

    OpenGLContextUniquePtr _context;
    OpenGLResourceExecutor _resourceExecutor;
    OpenGLRenderExecutor _renderExecutor;

    RingBuffer<ResourceContext *> _resourceContextBuffer;
    RingBuffer<RenderContext *> _renderContextBuffer;
};
} // namespace rendell