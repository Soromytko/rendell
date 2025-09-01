#pragma once
#include <rendell/ResourceId.h>

#include <config.h>

#include <algorithm>
#include <mutex>
#include <type_traits>
#include <utility>
#include <vector>

namespace rendell {
template <typename T> class ResourceIdStorage final {
    static_assert(std::is_base_of_v<ResourceId, T>, "This function only accepts ResourceId type");

    struct Resource final {
        bool isValid{false};
        uint16_t version{0};
    };

public:
    ResourceIdStorage(uint16_t size = config::resourceStorageIdCapacity) {
        _resources.resize(size);
    }

    ~ResourceIdStorage() = default;

    bool isValid(T resourceId) const {
        std::lock_guard<std::mutex> lock(_mutex);

        if (resourceId.version == 0 || resourceId.index >= _resources.size()) {
            return false;
        }
        if (resourceId.version != _resources[resourceId.index].version) {
            return false;
        }
        return true;
    }

    T alloc() {
        std::lock_guard<std::mutex> lock(_mutex);

        auto it = std::find_if(_resources.begin(), _resources.end(),
                               [](const Resource &container) { return !container.isValid; });
        if (it == _resources.end()) {
            // TODO: Should we resize the container?
            return T{0, 0};
        }
        it->isValid = true;
        if (it->version == 0) {
            it->version = 1;
        }

        const uint16_t index = static_cast<uint16_t>(std::distance(_resources.begin(), it));
        const uint16_t version = it->version;

        return T{index, version};
    }

    bool free(T resourceId) {
        std::lock_guard<std::mutex> lock(_mutex);

        if (resourceId.index >= _resources.size()) {
            return false;
        }

        Resource &resource = _resources[resourceId.index];
        resource.isValid = false;
        resource.version++;
        return true;
    }

private:
    std::vector<Resource> _resources;
    mutable std::mutex _mutex;
};
} // namespace rendell
