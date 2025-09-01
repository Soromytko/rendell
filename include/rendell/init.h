#pragma once

namespace rendell {
enum class SpecificationAPI {
    OpenGL,
    Vulkan,
    DirectX12,
};

struct Initer {
    struct NativeView {
        void *nativeWindowHandle = nullptr;
        void *x11Display = nullptr;
    };

    SpecificationAPI api = SpecificationAPI::OpenGL;
    NativeView nativeView;
};

using NativeViewId = size_t;

bool init(const Initer &initer);
bool release();

NativeViewId registerNativeView(Initer::NativeView nativeView);
void unregisterNativeView(NativeViewId nativeViewId);
} // namespace rendell