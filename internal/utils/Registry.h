#pragma once
#include <cassert>
#include <shared_mutex>
#include <vector>

namespace rendell {
template <typename TEntry> class Registry final {
public:
    using Id = size_t;
    static constexpr Id InvalidId = 0;

    Registry(size_t capacity)
        : _entryStorage(capacity) {}

    Id registerEntry(TEntry *data) {
        assert(data);
        std::unique_lock lock(_mutex);
        for (size_t i = 0; i < _entryStorage.size(); i++) {
            if (_entryStorage[i] == nullptr) {
                _entryStorage[i] = data;
                return static_cast<Id>(i + 1);
            }
        }
        return InvalidId;
    }

    bool unregisterEntry(Id id) {
        if (isValidId(id)) {
            return false;
        }
        std::unique_lock lock(_mutex);
        const bool result = _entryStorage[idToIndex(id)] != nullptr;
        _entryStorage[idToIndex(id)] = nullptr;
        return result;
    }

    [[nodiscard]] std::shared_lock<std::shared_mutex> beginUsing(Id id, TEntry *&entry) {
        if (!isValidId(id)) {
            entry = nullptr;
            return std::shared_lock<std::shared_mutex>();
        }
        std::shared_lock<std::shared_mutex> lock(_mutex);
        entry = _entryStorage[idToIndex(id)];
        if (!entry) {
            lock.unlock();
        }
        return lock;
    }

    bool isValid(Id id) const {
        if (!isValidId(id)) {
            return false;
        }
        std::shared_lock lock(_mutex);
        return _entryStorage[idToIndex(id)] != nullptr;
    }

private:
    inline bool isValidId(Id id) const { return id != InvalidId && id <= _entryStorage.size(); }

    inline size_t idToIndex(Id id) const {
        assert(isValidId(id));
        return id - 1;
    }

    std::vector<TEntry *> _entryStorage;
    std::shared_mutex _mutex;
};
} // namespace rendell