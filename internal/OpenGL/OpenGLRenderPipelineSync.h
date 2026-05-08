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

    void submitResourceContext(std::unique_ptr<ResourceContext> resourceContext) override;
    void submitRenderContext(std::unique_ptr<RenderContext> renderContext) override;

    void waitAndRender() override;

private:
    void render();

    OpenGLContextUniquePtr _context;
    OpenGLResourceExecutor _resourceExecutor;
    OpenGLRenderExecutor _renderExecutor;

    RingBuffer<std::unique_ptr<ResourceContext>> _resourceContextBuffer;
    RingBuffer<std::unique_ptr<RenderContext>> _renderContextBuffer;
};
} // namespace rendell