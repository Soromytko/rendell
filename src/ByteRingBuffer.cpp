#include <Buffers/ByteRingBuffer.h>

#include <algorithm>
#include <cassert>
#include <cstring>

namespace rendell {
ByteRingBuffer::ByteRingBuffer(size_t chunkCapacity)
    : _chunkCapacity(chunkCapacity) {
    _headChunk = createChunk(_chunkCapacity);
    _tailChunk = _headChunk;
}

ByteRingBuffer::ChunkSharedPtr ByteRingBuffer::createChunk(size_t capacity) const {
    ChunkSharedPtr chunk = std::make_shared<Chunk>(capacity);
    return chunk;
}

void ByteRingBuffer::write(const uint8_t *inputData, size_t dataSize) {
    size_t remain = dataSize;
    while (remain > 0) {
        const size_t written = _tailChunk->write(inputData + (dataSize - remain), remain);
        remain -= written;
        _length += written;

        if (remain > 0) {
            assert(_tailChunk->isFull());
            if (!_tailChunk->getNext()) {
                ChunkSharedPtr newTailChunk = createChunk(_chunkCapacity);
                _tailChunk->setNext(newTailChunk);
            }
            _tailChunk = _tailChunk->getNext();
            assert(_tailChunk);
        }
    }
}

void ByteRingBuffer::read(uint8_t *outputData, size_t dataSize) {
    size_t totalRead = 0;
    while (totalRead < dataSize) {
        const size_t read = _headChunk->read(outputData + totalRead, dataSize - totalRead);
        totalRead += read;
        _length -= totalRead;

        if (_headChunk->isEmpty()) {
            // TODO: Debug warning?
            assert(_headChunk != _tailChunk);
            _headChunk = _headChunk->getNext();
        }
    }
}

void ByteRingBuffer::reset() {
    Chunk *chunk = _headChunk.get();
    while (chunk) {
        chunk->reset();
        chunk = chunk->getNext().get();
    }
    _tailChunk = _headChunk;
}

ByteRingBuffer::Chunk::Chunk(size_t capacity) {
    _capacity = capacity;
    uint8_t *rawData = new uint8_t[capacity];
    _data.reset(rawData);
}

void ByteRingBuffer::Chunk::setNext(ChunkSharedPtr next) {
    _next = next;
}

size_t ByteRingBuffer::Chunk::write(const uint8_t *inputData, size_t dataSize) {
    if (isFull() || dataSize == 0) {
        return 0;
    }

    const size_t freeSpace = _capacity - _currentDataSize;
    const size_t toWrite = std::min(dataSize, freeSpace);

    // Write first part (to end of buffer)
    const size_t firstPart = std::min(toWrite, _capacity - _tail);
    std::memcpy(_data.get() + _tail, inputData, firstPart * sizeof(uint8_t));

    // Write second part (wrap around)
    if (firstPart < toWrite) {
        const size_t secondPart = toWrite - firstPart;
        std::memcpy(_data.get(), inputData + firstPart, secondPart * sizeof(uint8_t));
        _tail = secondPart;
    } else {
        _tail = (_tail + firstPart) % _capacity;
    }

    _currentDataSize += toWrite;
    return toWrite;
}

size_t ByteRingBuffer::Chunk::read(uint8_t *outputData, size_t dataSize) {
    if (isEmpty() || dataSize == 0) {
        return 0;
    }

    const size_t toRead = std::min(dataSize, _currentDataSize);

    // Read first part (to end of buffer)
    const size_t firstPart = std::min(toRead, _capacity - _head);
    std::memcpy(outputData, _data.get() + _head, firstPart * sizeof(uint8_t));

    // Read second part (wrap around)
    if (firstPart < toRead) {
        const size_t secondPart = toRead - firstPart;
        std::memcpy(outputData + firstPart, _data.get(), secondPart * sizeof(uint8_t));
        _head = secondPart;
    } else {
        _head = (_head + firstPart) % _capacity;
    }

    _currentDataSize -= toRead;
    return toRead;
}

void ByteRingBuffer::Chunk::reset() {
    _tail = _head = 0;
    _currentDataSize = 0;
}
} // namespace rendell