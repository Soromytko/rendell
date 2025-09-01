#pragma once
#include <algorithm>
#include <memory>
#include <vector>

#include <config.h>

namespace rendell {
class ByteRingBuffer final {
private:
    class Chunk;

    using ChunkSharedPtr = std::shared_ptr<Chunk>;

    class Chunk final {
    public:
        Chunk(size_t capacity);

        inline bool isFull() const { return _tail == _head && _currentDataSize > 0; }

        inline bool isEmpty() const { return _currentDataSize == 0; }

        inline ChunkSharedPtr getNext() const { return _next; }

        void setNext(ChunkSharedPtr next);

        size_t write(const uint8_t *data, size_t dataSize);
        size_t read(uint8_t *dataSource, size_t dataSize);

        void reset();

    private:
        ChunkSharedPtr _next{nullptr};
        size_t _tail{0};
        size_t _head{0};
        size_t _currentDataSize{0};
        size_t _capacity{0};
        std::unique_ptr<uint8_t[]> _data{};
    };

public:
    ByteRingBuffer(size_t chunkCapacity = config::byteRingBufferChunkCapacity);
    ~ByteRingBuffer() = default;

    inline size_t getLength() const { return _length; }

    inline bool isEmpty() const { return _length == 0; }

    inline bool canRead(size_t size) const { return size <= _length; }

    template <typename T> ByteRingBuffer &operator<<(const T &data) {
        const uint8_t *dataPtr = reinterpret_cast<const uint8_t *>(&data);
        const size_t dataSize = sizeof(T);
        write(dataPtr, dataSize);
        return *this;
    }

    template <typename T> ByteRingBuffer &operator>>(T &data) {
        uint8_t *dataSourcePtr = reinterpret_cast<uint8_t *>(&data);
        const size_t dataSize = sizeof(T);
        read(dataSourcePtr, dataSize);
        return *this;
    }

    void reset();

private:
    ChunkSharedPtr createChunk(size_t capacity) const;

    void write(const uint8_t *inputData, size_t dataSize);
    void read(uint8_t *outputData, size_t dataSize);

    ChunkSharedPtr _headChunk;
    ChunkSharedPtr _tailChunk;
    size_t _chunkCapacity;
    size_t _length{0};
};
} // namespace rendell
