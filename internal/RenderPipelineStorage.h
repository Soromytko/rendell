#pragma once
#include "RenderPipeline.h"
#include <rendell/init_types.h>

namespace rendell {
class RenderPipelineStorage final {
public:
    using ReturnResourceCommandBufferCallback = std::function<void(ResourceCommandBuffer *buffer)>;
    using ReturnRenderCommandBufferCallback = std::function<void(RenderCommandBuffer *buffer)>;

    RenderPipelineStorage(ReturnResourceCommandBufferCallback resourceCallback,
                          ReturnRenderCommandBufferCallback renderCallback);
    ~RenderPipelineStorage() = default;

    const std::vector<NativeViewId> &getNativeViewIds() const;

    NativeViewId createRenderPipeline(SpecificationAPI api, NativeView nativeView,
                                      bool useSeparateRenderThread);
    bool releaseRenderPipeline(NativeViewId nativeViewId);
    RenderPipeline *getRenderPipeline(NativeViewId nativeViewId) const;

private:
    ReturnResourceCommandBufferCallback _resourceCallback;
    ReturnRenderCommandBufferCallback _renderCallback;

    std::vector<NativeViewId> _nativeViewIds;
    std::vector<std::unique_ptr<RenderPipeline>> _renderPipelines;
};
} // namespace rendell