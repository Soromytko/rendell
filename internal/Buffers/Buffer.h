#pragma once
#include <cassert>
#include <cstring>
#include <type_traits>
#include <vector>

namespace rendell {
template <typename T>
concept TriviallyCopyable = std::is_trivially_copyable_v<T>;

template <TriviallyCopyable T> class Buffer {
public:
    using value_type = T;

    explicit Buffer(size_t reservedSize = 1024) {
        _container.resize(reservedSize);
        _capacity = reservedSize;
        _writePos = 0;
    }

    virtual ~Buffer() = default;

    inline size_t getCapacity() const { return _capacity; }

    inline size_t getSize() const { return _writePos; }

    inline size_t getLength() const { return _writePos; }

    inline bool isEmpty() const { return _writePos == 0; }

    inline const T *getData() const { return _container.data(); }

    inline T *getData() { return _container.data(); }

    inline void reset() { _writePos = 0; }

    void clear() { _writePos = 0; }

    void reserve(size_t value) {
        if (value > _capacity) {
            _container.resize(value);
            _capacity = value;
        }
    }

    void append(T value) {
        growIfNeeded(1);
        _container[_writePos++] = value;
    }

    void write(const T *data, size_t size) {
        assert(data != nullptr);
        assert(size > 0);
        growIfNeeded(size);
        std::memcpy(_container.data() + _writePos, data, size * sizeof(T));
        _writePos += size;
    }

    void overwrite(size_t offset, const T *data, size_t size) {
        assert(data != nullptr);
        assert(size > 0);
        assert(offset + size <= _writePos);
        std::memcpy(_container.data() + offset, data, size * sizeof(T));
    }

    void read(size_t offset, T *outData, size_t size) const {
        assert(outData != nullptr);
        assert(size > 0);
        assert(offset + size <= _writePos);
        std::memcpy(outData, _container.data() + offset, size * sizeof(T));
    }

    T &operator[](size_t index) {
        assert(index < _writePos);
        return _container[index];
    }

    const T &operator[](size_t index) const {
        assert(index < _writePos);
        return _container[index];
    }

    auto begin() { return _container.begin(); }

    auto begin() const { return _container.begin(); }

    auto end() { return _container.begin() + _writePos; }

    auto end() const { return _container.begin() + _writePos; }

protected:
    void growIfNeeded(size_t addedDataSize = 1) {
        assert(addedDataSize > 0);
        const size_t required = _writePos + addedDataSize;
        if (required <= _capacity) {
            return;
        }
        const size_t newCapacity = std::max<size_t>(_capacity * _growthFactor, required);
        _container.resize(newCapacity);
        _capacity = newCapacity;
    }

    static constexpr size_t _growthFactor = 2;

    std::vector<T> _container;
    size_t _capacity = 0;
    size_t _writePos = 0;
};
} // namespace rendell
