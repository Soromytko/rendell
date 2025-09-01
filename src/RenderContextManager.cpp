#include <RenderContextManager.h>

#include <RenderContextImpl.h>
#include <rendell/RenderContext.h>

#include <algorithm>
#include <cassert>
#include <memory>

namespace rendell {
std::unique_ptr<RenderContextPool> s_renderContextPool{nullptr};

void RenderContextPool::init() {
    assert(!s_renderContextPool);
    s_renderContextPool = std::make_unique<RenderContextPool>();
}

void RenderContextPool::release() {
    assert(s_renderContextPool);
    s_renderContextPool.reset();
}

RenderContextPool *RenderContextPool::getInstance() {
    assert(s_renderContextPool);
    return s_renderContextPool.get();
}

RenderContextPool::RenderContextPool() {
    setSize(2);
}

size_t RenderContextPool::getSize() const {
    return _pool.size();
}

void RenderContextPool::setSize(size_t size) {
    assert(size >= 0);
    if (size == _pool.size()) {
        return;
    }
    const size_t oldSize = _pool.size();
    _pool.resize(size);

    if (oldSize < size) {
        return;
    }

    for (auto it = _pool.begin() + oldSize; it != _pool.end(); it++) {
        *it = std::make_unique<RenderContext>();
    }
}

RenderContext *RenderContextPool::getRenderContext() const {
    auto it = std::find_if(_pool.begin(), _pool.end(), [](RenderContextUniquePtr &renderContext) {
        return !renderContext->_impl->isBusy;
    });

    if (it != _pool.end()) {
        RenderContext *result = it->get();
        result->_impl->isBusy = true;
        return it->get();
    }
    return nullptr;
}

CommandBufferSharedPtr RenderContextPool::getCommandBufferAndSwap(RenderContext *renderContext) {
    assert(renderContext);
    renderContext->_impl->getBufferAndSwap();
}
} // namespace rendell

namespace rendell {
RenderContext *RenderContextManager::getRenderContext() {
    RenderContext *renderContext = s_renderContextPool.getRenderContext();
    if (!renderContext) {
        // TODO:  warning
        const auto size = s_renderContextPool.getSize();
        assert(size > 0);
        s_renderContextPool.setSize(size * 2);
        return getRenderContext();
    }
    return renderContext;
}

void returnThreadRenderer(ThreadRenderer *threadRenderer) {
    auto it = std::find_if(s_threadRenderers.begin(), s_threadRenderers.end(),
                           [=](const ThreadRendererWrapper &threadRendererWrapper) {
                               return threadRendererWrapper.threadRenderer.get() == threadRenderer;
                           });
    if (it != s_threadRenderers.end()) {
        it->isBusy = false;
    }
}
} // namespace rendell