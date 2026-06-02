#pragma once
#include <condition_variable>
#include <mutex>
#include <queue>

namespace rendell {
template <typename T> class ConcurrentQueue final {
public:
    ConcurrentQueue() = default;
    ~ConcurrentQueue() = default;

    ConcurrentQueue(const ConcurrentQueue &) = delete;
    ConcurrentQueue &operator=(const ConcurrentQueue &) = delete;
    ConcurrentQueue(ConcurrentQueue &&) = delete;
    ConcurrentQueue &operator=(ConcurrentQueue &&) = delete;
 
    inline size_t getCount() const {
        std::unique_lock<std::mutex> lock(_mutex);
        return _data.size();
    }

    T pop() {
        std::unique_lock<std::mutex> lock(_mutex);
        _conditionVariable.wait(lock, [this] { return !_data.empty(); });

        T result = std::move(_data.front());
        _data.pop();
        return result;
    }

    void push(T item) {
        {
            std::lock_guard<std::mutex> lock(_mutex);
            _data.push(std::move(item));
        }
        _conditionVariable.notify_one();
    }

private:
    std::queue<T> _data{};

    mutable std::mutex _mutex;
    std::condition_variable _conditionVariable;
};
} // namespace rendell