#include <ResourceContextPool.h>
#include <ResourceContextPool.h>

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
    assert(s_ResourceContextPool.getCount() == _size &&
           "Attempting to destroy pool while resources are still in use!");
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
    return _pool.getCount();
}

ResourceContext *ResourceContextPool::getResourceContext() {
    std::unique_ptr<ResourceContext> context = _pool.pop();
    assert(context);
    return context.release();
}

void ResourceContextPool::returnResourceContext(ResourceContext *context) {
    assert(context);
    _pool.push(std::unique_ptr<ResourceContext>(context));
}

void ResourceContextPool::setSize(size_t size) {
    assert(size >= 0);
    if (_size < size) {
        for (size_t i = 0; i < size - _size; i++) {
            _pool.push(std::make_unique<ResourceContext>());
            _size++;
        }
    } else if (_size > size) {
        _pool.pop();
        _size--;
    }
}
} // namespace rendell
