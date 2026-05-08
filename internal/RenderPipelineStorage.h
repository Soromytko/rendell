#pragma once
#include "RenderPipeline.h"
#include <rendell/init_types.h>

namespace rendell {
class RenderPipelineStorage final {
public:
    static void init();
    static void release();
    static RenderPipelineStorage *getInstance();

private:
    RenderPipelineStorage() = default;

public:
    ~RenderPipelineStorage() = default;

    const std::vector<NativeViewId> &getNativeViewIds() const;

    NativeViewId createRenderPipeline(SpecificationAPI api, NativeView nativeView,
                                      bool useSeparateRenderThread);
    void releaseRenderPipeline(NativeViewId nativeViewId);
    RenderPipeline *getRenderPipeline(NativeViewId nativeViewId) const;

private:
    std::vector<NativeViewId> _nativeViewIds;
    std::vector<std::unique_ptr<RenderPipeline>> _renderPipelines;
};
} // namespace rendell