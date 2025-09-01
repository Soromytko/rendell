#pragma once
#include <cstddef>

namespace rendell {
enum class SpecificationAPI {
    OpenGL45,
    Vulkan,
    DirectX12,
};

struct Initer {
    SpecificationAPI api = SpecificationAPI::OpenGL45;
};

struct NativeView {
    void *nativeWindowHandle = nullptr;
    void *x11Display = nullptr;
};

using NativeViewId = size_t;

constexpr NativeViewId InvalidNativeViewId = 0;
} // namespace rendell