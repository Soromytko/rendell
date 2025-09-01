#include "context_creation.h"
#include <Backend/Factory.h>
#include <RenderContextManager.h>
#include <cassert>
#include <logging.h>
#include <rendell/init.h>
#include <vector>

namespace rendell {
static bool s_isInitialized{false};
static Initer s_initer{};
static std::vector<NativeViewId> s_nativeViews{};
static std::vector<IContextUniquePtr> s_contexts;
} // namespace rendell

namespace rendell {
static void initFactory(SpecificationAPI api) {
    switch (api) {
    case SpecificationAPI::OpenGL: {
        initOpenGLFactory();
    } break;
    case SpecificationAPI::Vulkan: {
        initVulkanFactory();
    } break;
    case SpecificationAPI::DirectX12: {
        initDirectX12Factory();
    } break;
    default:
        assert(false);
    }
}

bool init(const Initer &initer) {
    assert(!s_isInitialized);

    s_initer = initer;
    registerNativeView(s_initer.nativeView);

    initFactory(initer.api);

    RenderContextPool::init();
    RenderContextPool::getInstance()->setSize(10);
}

bool release() {
    releaseFactory();
}

NativeViewId registerNativeView(Initer::NativeView nativeView) {
    IContextUniquePtr context = createContext(s_initer);
    assert(context);
    s_contexts.push_back(std::move(context));
}

void unregisterNativeView(NativeViewId nativeViewId) {
    auto it = std::find(s_nativeViews.begin(), s_nativeViews.end(), nativeViewId);
    if (it == s_nativeViews.end()) {
        RENDELL_WARNING("The {} nativeViewId is not valid", nativeViewId);
        return;
    }
    s_nativeViews.erase(it);
    s_contexts.erase(s_contexts.begin() + nativeViewId);
}

} // namespace rendell