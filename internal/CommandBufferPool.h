#pragma once
#include <Pool.h>

#include <cassert>
#include <memory>

namespace rendell {
class ResourceCommandBuffer;
class RenderCommandBuffer;

template <typename TCommandBuffer>
    requires std::same_as<TCommandBuffer, ResourceCommandBuffer> ||
             std::same_as<TCommandBuffer, RenderCommandBuffer>
class CommandBufferPool final {
public:
    using CommandBufferPtr = std::unique_ptr<TCommandBuffer>;

    CommandBufferPool(std::vector<CommandBufferPtr> buffers)
        : _bufferStorage(std::move(buffers))
        , _freeBuffers(_bufferStorage.size(),
                       [this](size_t i) { return _bufferStorage[i].get(); }) {
        assert(!_bufferStorage.empty());
    }

    ~CommandBufferPool() = default;

    CommandBufferPool(const CommandBufferPool &) = delete;
    CommandBufferPool &operator=(const CommandBufferPool &) = delete;
    CommandBufferPool(CommandBufferPool &&) = delete;
    CommandBufferPool &operator=(CommandBufferPool &&) = delete;

    inline size_t getCapacity() const { return _bufferStorage.size(); }

    inline size_t getCount() const { return _freeBuffers.getCount(); }

    TCommandBuffer *pop() { return _freeBuffers.pop(); }

    void push(TCommandBuffer *buffer) { _freeBuffers.push(buffer); }

private:
    std::vector<CommandBufferPtr> _bufferStorage;
    Pool<TCommandBuffer *> _freeBuffers;
};
} // namespace rendell
