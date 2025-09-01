#pragma once
#include <RenderPipeline.h>

#include "OpenGLContext.h"
#include "OpenGLRenderExecutor.h"
#include "OpenGLResourceExecutor.h"
#include <Buffers/RingBuffer.h>
#include <rendell/init_types.h>
#include <rendell/oop/raii.h>

#include <condition_variable>
#include <mutex>
#include <thread>

namespace rendell {
class OpenGLRenderPipeline final : public RenderPipeline {
public:
    OpenGLRenderPipeline(NativeView nativeView);
    ~OpenGLRenderPipeline();

    bool isInitialized() const override;
    const IContext *getContext() const override;

    void run() override;

    void submitResourceContext(ResourceContext *resourceContext) override;
    void submitRenderContext(RenderContext *renderContext) override;

    void waitAndRender() override;

    void rendering();

private:
    bool waitForRenderTask();

    OpenGLContextUniquePtr _context;
    OpenGLResourceExecutor _resourceExecutor;
    OpenGLRenderExecutor _renderExecutor;

    RingBuffer<ResourceContext *> _resourceContextBuffer;
    RingBuffer<RenderContext *> _renderContextBuffer;

    std::mutex _renderingMutex;

    std::thread _renderThread;
    std::condition_variable _renderThreadCV;
    bool _running{false};
    bool _hasRenderTask{false};
};

RENDELL_USE_RAII_FACTORY(OpenGLRenderPipeline)
} // namespace rendell