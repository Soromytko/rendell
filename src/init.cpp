#include <rendell/init.h>

#include "context_creation.h"
#include <RenderContextPool.h>
#include <RenderPipelineStorage.h>
#include <ResourceContextPool.h>
#include <config.h>

#include <cassert>
#include <logging.h>
#include <vector>

namespace rendell {
static bool s_isInitialized{false};
static Initer s_initer{};
static std::vector<NativeViewId> s_nativeViews{};
} // namespace rendell

namespace rendell {
bool init(const Initer &initer) {
    assert(!s_isInitialized);

    s_initer = initer;

    RenderPipelineStorage::init();
    ResourceContextPool::init(config::resourceContextPoolSize);
    RenderContextPool::init(config::renderContextPoolSize);

    return true;
}

void release() {
    RenderPipelineStorage::release();
    ResourceContextPool::release();
    RenderContextPool::release();
}

NativeViewId registerNativeView(NativeView nativeView) {
    const NativeViewId nativeViewId =
        RenderPipelineStorage::getInstance()->createRenderPipeline(s_initer.api, nativeView);
    s_nativeViews.push_back(nativeViewId);
    return nativeViewId;
}

void unregisterNativeView(NativeViewId nativeViewId) {
    auto it = std::find(s_nativeViews.begin(), s_nativeViews.end(), nativeViewId);
    if (it == s_nativeViews.end()) {
        RENDELL_WARNING("This is not valid NativeViewId: {}", static_cast<size_t>(nativeViewId));
        return;
    }
    RenderPipelineStorage::getInstance()->releaseRenderPipeline(nativeViewId);
    s_nativeViews.erase(it);
}

} // namespace rendell