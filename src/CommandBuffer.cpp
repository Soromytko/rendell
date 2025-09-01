#include <CommandBuffer.h>
#include <algorithm>
#include <cassert>

#define SCOPE_MUTEX(_mutex) std::lock_guard<std::mutex> lock(_mutex)

namespace rendell {
CommandBuffer::CommandBuffer(size_t capacity, size_t threadCount = 10) {
    _capacity = capacity;
    _data = new data_t[_capacity];

    setThreadCount(threadCount);
}

CommandBuffer::~CommandBuffer() {
    delete[] _data;

    for (auto it = _rawBuffers.begin(); it != _rawBuffers.end(); it++) {
        it->release();
    }
}

size_t CommandBuffer::getSize() const {
    return _capacity;
}

void CommandBuffer::setThreadCount(size_t count) {
    assert(count != 0);

    if (count == _rawBuffers.size()) {
        return;
    }

    if (count < _rawBuffers.size()) {
        std::vector<RawBuffer> newRawBuffers(_rawBuffers.begin(), _rawBuffers.begin() + count);
        for (auto it = _rawBuffers.begin() + count; it != _rawBuffers.end(); it++) {
            it->release();
        }
        _rawBuffers = std::move(newRawBuffers);
    } else {
        const size_t oldSize = _rawBuffers.size();
        _rawBuffers.resize(count);
        for (auto it = _rawBuffers.begin() + oldSize; it != _rawBuffers.end(); it++) {
            it->data = new data_t[_capacity];
        }
    }
}

bool CommandBuffer::write(const data_t *data, size_t size) {
    if (isFull()) {
        return false;
    }

    SCOPE_MUTEX(_writeMutex);

    if (_writeCursorPosition >= _readCursorPosition) {
        if (_writeCursorPosition + size < _capacity) {
            writeData(data, size, _writeCursorPosition);
            setWriteCursorPosition(size);
            return true;
        }
        if (_capacity - _writeCursorPosition + _readCursorPosition > size) {
            const size_t firstPartSize = size - (_capacity - _writeCursorPosition);
            const size_t secondPartSize = size - firstPartSize;
            writeData(data, firstPartSize, _writeCursorPosition);
            writeData(data + firstPartSize, secondPartSize, 0);
            setWriteCursorPosition(secondPartSize);
            return true;
        }
    } else {
        if (_readCursorPosition - _writeCursorPosition >= size) {
            writeData(data, size, _writeCursorPosition);
            setWriteCursorPosition(_writeCursorPosition + size);
            return true;
        }
    }

    return false;
}

bool CommandBuffer::read(data_t *data, size_t size) {
    if (_readCursorPosition == _writeCursorPosition) {
        return false;
    }

    SCOPE_MUTEX(_readMutex);

    if (_readCursorPosition < _writeCursorPosition) {
        if (_readCursorPosition + size <= _writeCursorPosition) {
            readData(data, size, _readCursorPosition);
            setReadCursorPosition(_readCursorPosition + size);
            return true;
        }
    } else {
        if (_readCursorPosition + size <= _capacity) {
            readData(data, size, _readCursorPosition);
            setReadCursorPosition(_readCursorPosition + size);
            return true;
        }
        if (_capacity - _readCursorPosition + _writeCursorPosition >= size) {
            const size_t firstPartSize = size - (_capacity - _readCursorPosition);
            const size_t secondPartSize = size - firstPartSize;
            readData(data, firstPartSize, _readCursorPosition);
            readData(data + secondPartSize, secondPartSize, 0);
            setReadCursorPosition(secondPartSize);
            return true;
        }
    }

    return false;
}

CommandBuffer::RawBufferId CommandBuffer::startRawWriting() {
    SCOPE_MUTEX(_rawWritingMutex);

    auto it = std::find_if(_rawBuffers.begin(), _rawBuffers.end(),
                           [](const RawBuffer &rawBuffer) { return !rawBuffer.isBusy.load(); });
    if (it != _rawBuffers.end()) {
        it->isBusy = true;
        return std::distance(_rawBuffers.begin(), it);
    }

    return -1;
}

bool CommandBuffer::writeRaw(RawBufferId rawBufferId, const data_t *data, size_t size) {
    assert(rawBufferId >= 0);

    RawBuffer &rawBuffer = _rawBuffers[rawBufferId];

    if (rawBuffer.currentSize + size > _capacity) {
        return false;
    }
    std::memcpy(rawBuffer.data + rawBuffer.currentSize, data, size);
    rawBuffer.currentSize += size;
    return true;
}

bool CommandBuffer::commitRawWriting(RawBufferId rawBufferId) {
    assert(rawBufferId >= 0);

    RawBuffer &rawBuffer = _rawBuffers[rawBufferId];

    if (write(rawBuffer.data, rawBuffer.currentSize)) {
        rawBuffer.currentSize = 0;
        rawBuffer.isBusy = false;
        return true;
    }
    return false;
}

bool CommandBuffer::isFull() const {
    return _writeCursorPosition == _readCursorPosition && _ringNumber != 0;
}

void CommandBuffer::setWriteCursorPosition(size_t value) {
    value = value % _capacity;
    if (value < _writeCursorPosition) {
        _ringNumber++;
    }
    _writeCursorPosition = value;
}

void CommandBuffer::setReadCursorPosition(size_t value) {
    value = value % _capacity;
    if (value < _readCursorPosition) {
        _ringNumber--;
    }
    _readCursorPosition = value;
}

void CommandBuffer::writeData(const data_t *data, size_t size, size_t startIndex) {
    assert(startIndex + size <= _capacity);
    std::memcpy(_data + startIndex, data, size);
}

void CommandBuffer::readData(data_t *data, size_t size, size_t startIndex) {
    assert(startIndex + size <= _capacity);
    std::memcpy(data, _data + startIndex, size);
}

} // namespace rendell