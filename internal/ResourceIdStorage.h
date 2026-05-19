#pragma once
#include <rendell/ResourceId.h>

#include <config.h>
#include <utils/MPMC_Queue.h>

#include <algorithm>
#include <cassert>
#include <memory>
#include <type_traits>

namespace rendell {
template <typename T> class ResourceIdStorage final {
    static_assert(std::is_base_of_v<ResourceId, T>, "This function only accepts ResourceId type");

private:
    struct Resource final {
        std::atomic<bool> isValid{false};
        std::atomic<uint16_t> version{1};
    };

    uint16_t _size;
    MPMC_Queue<uint16_t> _freeQueue;
    std::unique_ptr<Resource[]> _resources;

public:
    ResourceIdStorage(uint16_t size = config::resourceStorageIdCapacity)
        : _size(size)
        , _freeQueue(size)
        , _resources(std::make_unique<Resource[]>(size)) {
        for (uint16_t i = 0; i < _size; i++) {
            const bool isEnqueueSuccessful = _freeQueue.enqueue(i);
            assert(isEnqueueSuccessful);
        }
    }

    ResourceIdStorage(const ResourceIdStorage &) = default;

    ~ResourceIdStorage() = default;

    bool isValid(T resourceId) const {
        if (resourceId.version == 0 || resourceId.index >= _size) {
            return false;
        }

        Resource &resource = _resources[resourceId.index];
        if (resourceId.version != resource.version.load(std::memory_order_relaxed)) {
            return false;
        }

        return resource.isValid.load(std::memory_order_relaxed);
    }

    T alloc() {
        uint16_t index;
        if (!_freeQueue.dequeue(index)) {
            return T{};
        }
        Resource &resource = _resources[index];
        resource.isValid.store(true, std::memory_order_release);
        const uint16_t version = resource.version.load(std::memory_order_relaxed);
        assert(version > 0);
        return T{
            index,
            version,
        };
    }

    bool free(T resourceId) {
        if (resourceId.version == 0 || resourceId.index >= _size) {
            return false;
        }

        Resource &resource = _resources[resourceId.index];
        auto version = resource.version.load(std::memory_order_relaxed);
        if (resourceId.version != version) {
            return false;
        }

        const auto nextVersion = std::max(uint16_t(1), uint16_t(version + 1));
        if (!resource.version.compare_exchange_weak(version, nextVersion,
                                                    std::memory_order_relaxed)) {
            return false;
        }

        resource.isValid.store(false, std::memory_order_relaxed);
        const bool isEnqueueSuccessful = _freeQueue.enqueue(resourceId.index);
        assert(isEnqueueSuccessful);
        return true;
    }
};
} // namespace rendell
