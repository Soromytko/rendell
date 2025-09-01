#pragma once
#include <condition_variable>
#include <mutex>
#include <queue>

namespace rendell {
template <typename T> class Pool {
public:
    Pool() = default;
    virtual ~Pool() = default;

    inline size_t getCount() const { return _count; }

    T pop() {
        std::unique_lock<std::mutex> lock(_mutex);
        _conditionVariable.wait(lock, [this] { return !_data.empty(); });

        T result = _data.front();
        _data.pop();
        _count--;
        return result;
    }

    void push(const T &item) {
        {
            std::lock_guard<std::mutex> lock(_mutex);
            _data.push(item);
            _count++;
        }
        _conditionVariable.notify_one();
    }

private:
    size_t _size;
    size_t _count;
    std::queue<T> _data;

    std::mutex _mutex;
    std::condition_variable _conditionVariable;
};
} // namespace rendell