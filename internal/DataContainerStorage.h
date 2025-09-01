#pragma once
#include <rendell/DataContainer.h>
#include <rendell/DataType.h>

#include <unordered_map>

namespace rendell {
template <typename T> class DataContainerStorage final {
public:
    using key_t = size_t;

    key_t store(DataContainer<T> dataContainer) {
        const key_t key = generateKey();
        auto result = _storage.emplace(key, std::move(dataContainer));
        assert(result.second);
        assert(_storage.find(key) != _storage.end());
        return key;
    }

    DataContainer<T> retrieve(key_t key) {
        auto it = _storage.find(key);
        assert(it != _storage.end());
        DataContainer<T> result = it->second;
        _storage.erase(it);
        return result;
    }

private:
    inline key_t generateKey() const { return ++_keyCounter; }

    mutable key_t _keyCounter{};

    std::unordered_map<key_t, DataContainer<T>> _storage;
};

DataContainerStorage<index_t> &getIndexBufferDataContainerStorage();
DataContainerStorage<vertex_t> &getVertexBufferDataContainerStorage();
} // namespace rendell