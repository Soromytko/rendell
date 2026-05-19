#pragma once
#include <utils/Registry.h>

namespace rendell {
class Instance;

class InstanceRegistry final {
public:
    static InstanceRegistry &getInstance() {
        static InstanceRegistry instance;
        return instance;
    }

    InstanceRegistry(const InstanceRegistry &) = delete;
    InstanceRegistry &operator=(const InstanceRegistry &) = delete;
    InstanceRegistry(InstanceRegistry &&) = delete;
    InstanceRegistry &operator=(InstanceRegistry &&) = delete;

    Registry<Instance> &getRegistry() { return _registry; }

private:
    InstanceRegistry(size_t capacity = 12)
        : _registry(capacity) {}

    Registry<Instance> _registry;
};

} // namespace rendell