#pragma once
#include "Pool.h"
#include "ResourceContext.h"

#include <unordered_set>

namespace rendell {
class ResourceContextPool final {
public:
    static void init(size_t size);
    static void release();
    static ResourceContextPool *getInstance();

private:
    ResourceContextPool(size_t size);

public:
    ~ResourceContextPool() = default;

    size_t getSize() const;
    size_t getCount() const;

    ResourceContext *getResourceContext();
    void returnResourceContext(ResourceContext *renderContext);

private:
    void setSize(size_t size);

    size_t _size{0};

    Pool<ResourceContextSharedPtr> _freed;
    std::unordered_set<ResourceContextSharedPtr> _used;

    std::mutex _mutex{};
};
} // namespace rendell
