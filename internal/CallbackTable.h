#pragma once
#include <cassert>
#include <optional>
#include <unordered_map>

namespace rendell {
template <typename TKey, typename TCallback> class CallbackTable final {
public:
    using Map = std::unordered_map<TKey, TCallback>;

    CallbackTable() = default;
    ~CallbackTable() = default;

    void add(TKey key, TCallback callback) {
        assert(callback);
        _callbacks[key] = callback;
    }

    std::optional<TCallback> tyrRetrive(TKey key) {
        auto it = _callbacks.find(key);
        if (it == _callbacks.end()) {
            return std::nullopt;
        }
        TCallback callback = it->second;
        _callbacks.erase(it);
        return callback;
    }

private:
    Map _callbacks;
};
} // namespace rendell

#include <rendell/DataType.h>
#include <rendell/ResourceId.h>

namespace rendell {
CallbackTable<size_t, ResultCallback> &getResultCallbackTable();
} // namespace rendell