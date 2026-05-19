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
            return result;
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

    template <typename ArgsT, typename ChunkT> class UniversalIterator {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = ArgsT;
        using difference_type = std::ptrdiff_t;
        using pointer = ArgsT *;
        using reference = ArgsT &;

        UniversalIterator(ChunkT *chunk, size_t index, size_t remainingElementCount)
            : _currentChunk(chunk)
            , _index(index)
            , _remaining(remainingElementCount) {}

        template <typename OtherArgs, typename OtherChunk>
        UniversalIterator(const UniversalIterator<OtherArgs, OtherChunk> &other)
            : _currentChunk(other.getChunk())
            , _index(other.getIndex())
            , _remaining(other.getRemaining()) {}

        reference operator*() const { return _currentChunk->data[_index]; }

        pointer operator->() const { return &_currentChunk->data[_index]; }

        UniversalIterator &operator++() {
            if (_remaining == 0)
                return *this;
            _remaining--;
            if (_remaining == 0) {
                _currentChunk = nullptr;
                _index = 0;
            } else {
                _index = (_index + 1) % _currentChunk->getCapacity();
                if (_index == _currentChunk->tail && _currentChunk->next) {
                    _currentChunk = _currentChunk->next.get();
                    _index = _currentChunk->head;
                }
            }
            return *this;
        }

        UniversalIterator operator++(int) {
            UniversalIterator tmp = *this;
            ++(*this);
            return tmp;
        }

        template <typename UA, typename UC>
        friend bool operator==(const UniversalIterator &a, const UniversalIterator<UA, UC> &b) {
            return a._remaining == b.getRemaining() && a._currentChunk == b.getChunk() &&
                   a._index == b.getIndex();
        }

        template <typename UA, typename UC>
        friend bool operator!=(const UniversalIterator &a, const UniversalIterator<UA, UC> &b) {
            return !(a == b);
        }

        ChunkT *getChunk() const { return _currentChunk; }

        size_t getIndex() const { return _index; }

        size_t getRemaining() const { return _remaining; }

    private:
        ChunkT *_currentChunk;
        size_t _index;
        size_t _remaining;
    };

    using iterator = UniversalIterator<T, Chunk>;
    using const_iterator = UniversalIterator<const T, const Chunk>;

    iterator begin() {
        if (isEmpty())
            return end();
        return iterator(_headChunk.get(), _headChunk->head, _length);
    }

    iterator end() { return iterator(nullptr, 0, 0); }

    const_iterator begin() const {
        if (isEmpty())
            return end();
        return const_iterator(_headChunk.get(), _headChunk->head, _length);
    }

    const_iterator end() const { return const_iterator(nullptr, 0, 0); }

private:
    inline ChunkPtr createChunk(size_t capacity) const { return std::make_unique<Chunk>(capacity); }

    ChunkPtr _headChunk;
    Chunk *_tailChunk;
    size_t _chunkCapacity;
    size_t _length{0};
};
} // namespace rendell
