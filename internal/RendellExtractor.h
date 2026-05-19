#pragma once
#include <rendell/RenderCommandBuffer.h>
#include <rendell/ResourceCommandBuffer.h>

namespace rendell {
class RenderCommandBufferImpl;
class ResourceCommandBufferImpl;

struct RendellExtractor {
    static ResourceCommandBufferImpl &extractImpl(ResourceCommandBuffer &buffer) {
        return *reinterpret_cast<ResourceCommandBufferImpl *>(buffer._implStorage);
    }

    static RenderCommandBufferImpl &extractImpl(RenderCommandBuffer &buffer) {
        return *reinterpret_cast<RenderCommandBufferImpl *>(buffer._implStorage);
    }
};
} // namespace rendell