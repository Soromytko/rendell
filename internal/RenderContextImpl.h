#pragma once
#include <DrawCallState.h>
#include <rendell/RenderContext.h>

namespace rendell {
struct CommandBufferPair final {
    CommandBufferPair() {
        prepareCommandBuffer = std::make_unique<CommandBuffer>();
        runtimeCommandBuffer = std::make_unique<CommandBuffer>();
    }

    CommandBufferUniquePtr prepareCommandBuffer;
    CommandBufferUniquePtr runtimeCommandBuffer;
};

using CommandBufferPairSharedPtr = std::shared_ptr<CommandBufferPair>;

struct RenderContext::Impl final {
    CommandBufferPairSharedPtr firstCommandBufferPair;
    CommandBufferPairSharedPtr secondCommandBufferPair;
    CommandBufferPair *currentCommandBufferPair;
    DrawCallState currentDrawCallState;
    std::vector<DrawCallState> drawCallStates{UINT16_MAX};
    uint16_t drawCallCount{0};
    bool isBusy{false};

    CommandBufferPairSharedPtr getCurrentCommandBufferPair();

    void swapCommandBufferPair();

    void submit();

    CommandBufferSharedPtr getBufferAndSwap()
    {

    }
};

} // namespace rendell