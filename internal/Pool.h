#pragma once
#include <utils/ConcurrentQueue.h>

#include <cassert>
#include <functional>
#include <memory>

namespace rendell {
template <typename T> class Pool final {
public:
    using Delegate = std::function<T(size_t index)>;

    Pool(size_t capacity, Delegate delegate)
        : _capacity(capacity) {
        assert(delegate);
        fill(delegate);
    }

    ~Pool() = default;

    Pool(const Pool &) = delete;
    Pool &operator=(const Pool &) = delete;
    Pool(Pool &&) = delete;
    Pool &operator=(Pool &&) = delete;

    inline size_t getCapacity() const { return _capacity; }

    inline size_t getCount() const { return _queue.getCount(); }

    T pop() { return _queue.pop(); }

    void push(T context) {
        assert(context);
        _queue.push(std::move(context));
    }

private:
    void fill(Delegate delegate) {
        for (size_t i = 0; i < _capacity; i++) {
            _queue.push(delegate(i));
        }
    }

    size_t _capacity;
    ConcurrentQueue<T> _queue{};
};
} // namespace rendell
