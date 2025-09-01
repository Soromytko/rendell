#pragma once
#include <cassert>
#include <memory>
#include <vector>

namespace rendell {
template <typename T> class DataContainer final {
public:
    DataContainer(const T *data, size_t size) {
        assert(data);
        assert(size > 0);
        _dataPtr = std::make_shared<std::vector<T>>(data, data + size);
    }

    DataContainer(const DataContainer<T> &other) { _dataPtr = other._dataPtr; }

    size_t getSize() const noexcept { return _dataPtr ? _dataPtr->size() : 0; }

    const T *getData() const noexcept { return _dataPtr ? _dataPtr->data() : nullptr; }

private:
    std::shared_ptr<std::vector<T>> _dataPtr;
};

} // namespace rendell