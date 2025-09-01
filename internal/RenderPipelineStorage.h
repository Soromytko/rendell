#pragma once
#include "RenderPipeline.h"
#include <rendell/init_types.h>

#include <functional>

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

    NativeViewId createRenderPipeline(SpecificationAPI api, NativeView nativeView);
    void releaseRenderPipeline(NativeViewId nativeViewId);
    RenderPipelineSharedPtr getRenderPipeline(NativeViewId nativeViewId) const;

private:
    std::vector<NativeViewId> _nativeViewIds;
    std::vector<RenderPipelineSharedPtr> _renderPipelines;
};
} // namespace rendell