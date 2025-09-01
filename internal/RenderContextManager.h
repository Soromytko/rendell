#pragma once
#include <cassert>
#include <vector>

#include <CommandBuffer.h>

namespace rendell {
class RenderContext;
} // namespace rendell

namespace rendell {
class RenderContextPool final {
    using RenderContextUniquePtr = std::unique_ptr<RenderContext>;

public:
    static void init();
    static void release();
    static RenderContextPool *getInstance();

private:
    RenderContextPool() = default;

public:
    ~RenderContextPool() = default;

    size_t getSize() const;
    RenderContext *getRenderContext() const;
    CommandBufferSharedPtr getCommandBufferAndSwap(RenderContext *renderContext);

    void setSize(size_t size);

private:
    std::vector<RenderContextUniquePtr> _pool;
};
} // namespace rendell
