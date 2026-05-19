#include <RendellState.h>

#include <cassert>

namespace rendell {
static RendellState *s_instance{nullptr};

void RendellState::init(Initer initer) {
    assert(!s_instance);
    s_instance = new RendellState(initer);
}

void RendellState::release() {
    assert(s_instance);
    delete s_instance;
    s_instance = nullptr;
}

RendellState &RendellState::getInstance() {
    assert(s_instance);
    return *s_instance;
}

RendellState::RendellState(Initer initer)
    : _initer(initer) {
    _nativeViews.clear();
    RenderPipelineStorage::init();
}

} // namespace rendell
