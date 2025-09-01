#include <ResourceContextPool.h>

#include <algorithm>
#include <cassert>
#include <memory>

namespace rendell {
static std::unique_ptr<ResourceContextPool> s_ResourceContextPool{nullptr};

void ResourceContextPool::init(size_t size) {
    assert(!s_ResourceContextPool);
    s_ResourceContextPool.reset(new ResourceContextPool(size));
}

void ResourceContextPool::release() {
    assert(s_ResourceContextPool);
    s_ResourceContextPool.reset();
}

ResourceContextPool *ResourceContextPool::getInstance() {
    assert(s_ResourceContextPool);
    return s_ResourceContextPool.get();
}

ResourceContextPool::ResourceContextPool(size_t size) {
    setSize(size);
}

size_t ResourceContextPool::getSize() const {
    return _size;
}

size_t ResourceContextPool::getCount() const {
    return _freed.getCount();
}

ResourceContext *ResourceContextPool::getResourceContext() {
    ResourceContextSharedPtr result = _freed.pop();
    assert(result);
    std::lock_guard<std::mutex> lock(_mutex);
    _used.insert(result);
    return result.get();
}

void ResourceContextPool::returnResourceContext(ResourceContext *resourceContext) {

    ResourceContextSharedPtr resourceContextPtr;
    {
        std::lock_guard<std::mutex> lock(_mutex);
        auto it = std::find_if(_used.begin(), _used.end(),
                               [&](const ResourceContextSharedPtr &currentResourceContext) {
                                   return currentResourceContext.get() == resourceContext;
                               });
        assert(it != _used.end());
        resourceContextPtr = *it;
        _used.erase(it);
    }
    assert(resourceContextPtr);
    _freed.push(resourceContextPtr);
}

void ResourceContextPool::setSize(size_t size) {
    assert(size >= 0);
    if (_size < size) {
        for (size_t i = 0; i < size - _size; i++) {
            _freed.push(makeResourceContext());
            _size++;
        }
    } else if (_size > size) {
        _freed.pop();
        _size--;
    }
}
} // namespace rendell
