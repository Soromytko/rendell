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
    bool useSeparateRenderThread = true;
    uint16_t maxResourceIdCount = 0xFFFF;
    uint16_t maxResourceCommandBufferPerFrame = 100;
    uint16_t maxRenderCommandBufferPerFrame = 100;
    size_t garbageCollectorLockFreeCapacity = 0xFFFF;
};

struct NativeView {
    void *nativeWindowHandle = nullptr;
    void *x11Display = nullptr;
};

using NativeViewId = size_t;

constexpr NativeViewId InvalidNativeViewId = 0;
} // namespace rendell