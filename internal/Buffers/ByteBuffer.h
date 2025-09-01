#pragma once
#include "Buffer.h"

#include <type_traits>

namespace rendell {
class ByteBuffer final : public Buffer<std::byte> {
public:
    ByteBuffer(size_t reservedSize)
        : Buffer<std::byte>(reservedSize) {}

    template <TriviallyCopyable TValue> ByteBuffer &operator<<(const TValue &value) {
        const size_t misalign = _writePos % alignof(TValue);
        if (misalign != 0) {
            _writePos += (alignof(TValue) - misalign);
        }
        growIfNeeded(sizeof(TValue));
        std::memcpy(_container.data() + _writePos, &value, sizeof(TValue));
        _writePos += sizeof(TValue);
        return *this;
    }
};

class ByteBufferReader final {
public:
    ByteBufferReader(const ByteBuffer &buffer, size_t offset = 0)
        : _buffer(buffer)
        , _offset(offset) {}

    inline bool isEmpty() const { return _offset >= _buffer.getSize(); }

    bool canRead(size_t size, size_t alignment = 1) const {
        return _offset + getMisalign(alignment) + size <= _buffer.getSize();
    }

    inline size_t getOffset() const { return _offset; }

    void jump(size_t offset) {
        assert(offset <= _buffer.getSize());
        _offset = offset;
    }

    template <TriviallyCopyable T> T read() {
        alignOffset(alignof(T));
        assert(_offset + sizeof(T) <= _buffer.getSize());
        const size_t offset = _offset;
        _offset += sizeof(T);
        return *reinterpret_cast<const T *>(_buffer.getData() + offset);
    }

    template <TriviallyCopyable T> void readArray(T *array, size_t size) {
        alignOffset(alignof(T));
        assert(_offset + sizeof(T) * size <= _buffer.getSize());
        std::memcpy(array, _buffer.getData() + _offset, size * sizeof(T));
        _offset += size * sizeof(T);
    }

    template <TriviallyCopyable T> const T *readArrayAsRef(size_t size) {
        alignOffset(alignof(T));
        assert(_offset + sizeof(T) * size <= _buffer.getSize());
        const T *result = reinterpret_cast<const T *>(_buffer.getData() + _offset);
        _offset += size * sizeof(T);
        return result;
    }

    template <TriviallyCopyable T> ByteBufferReader &operator>>(T &value) {
        alignOffset(alignof(T));
        assert(_offset + sizeof(T) <= _buffer.getSize());
        value = *reinterpret_cast<const T *>(_buffer.getData() + _offset);
        _offset += sizeof(T);
        return *this;
    }

private:
    inline size_t getMisalign(size_t alignment) const { return _offset % alignment; }

    void alignOffset(size_t alignment) {
        const size_t misalign = getMisalign(alignment);
        if (misalign != 0) {
            _offset += (alignment - misalign);
        }
    }

    const ByteBuffer &_buffer;
    size_t _offset;
};
} // namespace rendell
