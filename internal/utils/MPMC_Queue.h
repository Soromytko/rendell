#pragma once
#include <atomic>
#include <bit>
#include <cassert>
#include <cstddef>
#include <cstdint>
#include <memory>

//.https://sites.google.com/site/1024cores/home/lock-free-algorithms/queues/bounded-mpmc-queue
template <typename T> class MPMC_Queue final {
private:
    struct Cell {
        std::atomic<size_t> sequence;
        T data;
    };

    const size_t _bufferCapacity;
    const size_t _bufferMask;
    alignas(64) std::unique_ptr<Cell[]> _buffer;
    alignas(64) std::atomic<size_t> _tail;
    alignas(64) std::atomic<size_t> _head;

public:
    MPMC_Queue(size_t capacity)
        : _bufferCapacity(std::bit_ceil(capacity))
        , _bufferMask(_bufferCapacity - 1)
        , _buffer(std::make_unique<Cell[]>(_bufferCapacity)) {
        for (size_t i = 0; i < _bufferCapacity; i++) {
            _buffer[i].sequence.store(i, std::memory_order_relaxed);
        }
    }

    MPMC_Queue(const MPMC_Queue &) = delete;
    MPMC_Queue(MPMC_Queue &&) = delete;

    bool enqueue(T data) {
        Cell *cell{};
        auto tail = _tail.load(std::memory_order_relaxed);
        while (true) {
            cell = &_buffer[_tail & _bufferMask];
            const auto sequence = cell->sequence.load(std::memory_order_acquire);
            const auto diff = static_cast<intptr_t>(sequence) - static_cast<intptr_t>(tail);
            if (diff == 0) {
                if (_tail.compare_exchange_weak(tail, tail + 1, std::memory_order_relaxed)) {
                    break;
                }
            } else if (diff < 0) {
                return false;
            } else {
                tail = _tail.load(std::memory_order_relaxed);
            }
        }
        assert(cell);

        cell->data = std::move(data);
        cell->sequence.store(tail + 1, std::memory_order_release);

        return true;
    }

    bool dequeue(T &result) {
        Cell *cell{};
        auto head = _head.load(std::memory_order_relaxed);
        while (true) {
            cell = &_buffer[_head & _bufferMask];
            const auto sequence = cell->sequence.load(std::memory_order_acquire);
            const auto diff = static_cast<intptr_t>(sequence) - static_cast<intptr_t>(head + 1);
            if (diff == 0) {
                if (_head.compare_exchange_weak(head, head + 1, std::memory_order_relaxed)) {
                    break;
                }
            } else if (diff < 0) {
                return false;
            } else {
                head = _head.load(std::memory_order_relaxed);
            }
        }
        assert(cell);

        result = std::move(cell->data);
        cell->sequence.store(head + _bufferCapacity, std::memory_order_release);

        return true;
    }
};
