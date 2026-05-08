#pragma once
#include <algorithm>
#include <cassert>
#include <memory>
#include <vector>

#include <config.h>

namespace rendell {
template <typename T> class RingBuffer final {
private:
    struct Chunk;

    using ChunkPtr = std::unique_ptr<Chunk>;

    struct Chunk final {
        ChunkPtr next{nullptr};
        size_t tail{0};
        size_t head{0};
        size_t length{0};
        std::vector<T> data;

        Chunk(size_t capacity) { data.resize(capacity); }

        inline size_t getCapacity() const { return data.size(); }

        inline bool isFull() const { return tail == head && length > 0; }

        inline bool isEmpty() const { return length == 0; }

        void reset() {
            tail = head = 0;
            length = 0;
        }

        void push(T value) {
            assert(!isFull());
            data[tail] = std::move(value);
            tail = (tail + 1) % data.size();
            length++;
        }

        T pop() {
            assert(!isEmpty());
            T result = std::move(data[head]);
            head = (head + 1) % data.size();
            length--;
            return std::move(result);
        }
    };

public:
    RingBuffer(size_t chunkCapacity = config::ringBufferChunkCapacity) {
        _chunkCapacity = chunkCapacity;
        _headChunk = createChunk(_chunkCapacity);
        _tailChunk = _headChunk.get();
    }

    ~RingBuffer() = default;

    inline size_t getLength() const { return _length; }

    inline size_t isEmpty() const { return _length == 0; }

    void reset() {
        _length = 0;
        Chunk *currentChunk = _headChunk.get();
        while (currentChunk) {
            currentChunk->reset();
            currentChunk = currentChunk->next.get();
        }
        _tailChunk = _headChunk.get();
    }

    void push(T value) {
        if (_tailChunk->isFull()) {
            if (!_tailChunk->next) {
                _tailChunk->next = createChunk(_chunkCapacity);
            }
            _tailChunk = _tailChunk->next.get();
        }
        _tailChunk->push(std::move(value));
        _length++;
    }

    T pop() {
        assert(_length > 0);
        T result = _headChunk->pop();
        if (_headChunk->isEmpty() && _headChunk.get() != _tailChunk) {
            _headChunk = std::move(_headChunk->next);
        }
        _length--;
        return result;
    }

private:
    inline ChunkPtr createChunk(size_t capacity) const { return std::make_unique<Chunk>(capacity); }

    ChunkPtr _headChunk;
    Chunk *_tailChunk;
    size_t _chunkCapacity;
    size_t _length{0};
};
} // namespace rendell
