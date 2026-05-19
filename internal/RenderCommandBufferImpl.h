#pragma once
#include <Buffers/ByteBuffer.h>
#include <DrawCallState.h>
#include <config.h>

namespace rendell {
struct RenderCommandBufferImpl final {
    DrawCallStateList drawCallStates{config::drawCallStateListCapacity};
    DrawCallState currentDrawCallState{};
    ByteBuffer commandBuffer{config::renderCommandBufferSize};
    ByteBuffer uniformBuffer{config::uniformBufferSize};

    inline void reset() {
        drawCallStates.reset();
        commandBuffer.reset();
        uniformBuffer.reset();
        currentDrawCallState.reset();
    }

    inline static RenderCommandBufferImpl &getFromStorage(std::byte *storage) {
        return *reinterpret_cast<RenderCommandBufferImpl *>(storage);
    }
};
} // namespace rendell