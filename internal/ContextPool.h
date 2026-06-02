#pragma once
#include <utils/ConcurrentQueue.h>

#include <memory>

namespace rendell {
template <typename TResource> class ContextPool final {
public:
    ContextPool(size_t size) { setSize(size); }

    ~ContextPool() = default;

    ContextPool(const ContextPool &) = delete;
    ContextPool &operator=(const ContextPool &) = delete;
    ContextPool(ContextPool &&) = delete;
    ContextPool &operator=(ContextPool &&) = delete;

    size_t getSize() const { return _size; }

    size_t getCount() const { return _pool.getCount(); }

    std::unique_ptr<TResource> getContext() {
        std::unique_ptr<TResource> context = _pool.pop();
        assert(context);
        return context;
    }

    void returnContext(std::unique_ptr<TResource> context) {
        assert(context);
        _pool.push(std::move(context));
    }

private:
    void setSize(size_t size) {
        assert(size >= 0);
        if (_size < size) {
            for (size_t i = 0; i < size - _size; i++) {
                _pool.push(std::make_unique<TResource>());
                _size++;
            }
        } else if (_size > size) {
            _pool.pop();
            _size--;
        }
        _size = size;
    }

    size_t _size{0};

    ConcurrentQueue<std::unique_ptr<TResource>> _pool{};
};
} // namespace rendell
