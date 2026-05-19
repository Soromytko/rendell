#pragma once
#include <RenderPipeline.h>

#include "OpenGLContext.h"
#include "OpenGLRenderExecutor.h"
#include "OpenGLResourceExecutor.h"
#include <Buffers/RingBuffer.h>
#include <rendell/init_types.h>

#include <condition_variable>
#include <mutex>
#include <thread>

namespace rendell {
class ResourceCommandBuffer;
class RenderCommandBuffer;

class OpenGLRenderPipeline final : public RenderPipeline {
public:
    OpenGLRenderPipeline(NativeView nativeView, Callbacks callbacks);
    ~OpenGLRenderPipeline();

    bool isInitialized() const override;
    const IContext *getContext() const override;

    const ReleasedResourceIds &getReleasedResourceIds() const override {
        return _resourceExecutor.getReleasedResourceIds();
    }

    void run() override;

    void submitResourceContext(ResourceCommandBuffer *buffer) override;
    void submitRenderContext(RenderCommandBuffer *buffer) override;

    void waitAndRender() override;

    void rendering();

private:
    bool waitForRenderTask();

    OpenGLContextUniquePtr _context;
    OpenGLResourceExecutor _resourceExecutor;
    OpenGLRenderExecutor _renderExecutor;

    RingBuffer<ResourceCommandBuffer *> _resourceCommandBuffers;
    RingBuffer<RenderCommandBuffer *> _renderCommandBuffers;

    std::mutex _renderingMutex;

    std::thread _renderThread;
    std::condition_variable _renderThreadCV;
    bool _running{false};
    bool _hasRenderTask{false};
};
} // namespace rendell