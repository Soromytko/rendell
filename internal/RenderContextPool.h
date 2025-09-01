#pragma once
#include "Pool.h"
#include "RenderContext.h"
#include <config.h>

#include <mutex>
#include <unordered_set>

namespace rendell {
class RenderContextPool final {
public:
    static void init(size_t size);
    static void release();
    static RenderContextPool *getInstance();

private:
    RenderContextPool(size_t size);

public:
    ~RenderContextPool() = default;

    size_t getSize() const;
    size_t getCount() const;

    RenderContext *getRenderContext();
    void returnRenderContext(RenderContext *renderContext);

private:
    void setSize(size_t size);

    size_t _size{0};

    Pool<RenderContextSharedPtr> _freed;
    std::unordered_set<RenderContextSharedPtr> _used;

    std::mutex _mutex;
};
} // namespace rendell
