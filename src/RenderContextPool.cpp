#include <RenderContextPool.h>

#include <algorithm>
#include <cassert>

namespace rendell {
static std::unique_ptr<RenderContextPool> s_renderContextPool{nullptr};

void RenderContextPool::init(size_t size) {
    assert(!s_renderContextPool);
    s_renderContextPool.reset(new RenderContextPool(size));
}

void RenderContextPool::release() {
    assert(s_renderContextPool);
    s_renderContextPool.reset();
}

RenderContextPool *RenderContextPool::getInstance() {
    assert(s_renderContextPool);
    return s_renderContextPool.get();
}

RenderContextPool::RenderContextPool(size_t size) {
    setSize(size);
}

size_t RenderContextPool::getSize() const {
    return _size;
}

size_t RenderContextPool::getCount() const {
    return _freed.getCount();
}

RenderContext *RenderContextPool::getRenderContext() {
    RenderContextSharedPtr result = _freed.pop();
    assert(result);
    std::lock_guard<std::mutex> lock(_mutex);
    _used.insert(result);
    return result.get();
}

void RenderContextPool::returnRenderContext(RenderContext *renderContext) {

    RenderContextSharedPtr renderContextPtr;
    {
        std::lock_guard<std::mutex> lock(_mutex);
        auto it = std::find_if(_used.begin(), _used.end(),
                               [&](const RenderContextSharedPtr &currentRenderContext) {
                                   return currentRenderContext.get() == renderContext;
                               });
        assert(it != _used.end());
        renderContextPtr = *it;
        _used.erase(it);
    }
    assert(renderContextPtr);
    _freed.push(renderContextPtr);
}

void RenderContextPool::setSize(size_t size) {
    assert(size >= 0);
    if (_size < size) {
        for (size_t i = 0; i < size - _size; i++) {
            _freed.push(makeRenderContext());
            _size++;
        }
    } else if (_size > size) {
        _freed.pop();
        _size--;
    }
}
} // namespace rendell
