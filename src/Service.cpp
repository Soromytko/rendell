#include <rendell/Service.h>

#include <InstanceRegistry.h>
#include <rendell/Instance.h>

namespace rendell {
std::shared_lock<std::shared_mutex> rendell::beginUsingInstance(InstanceId id, Instance *&result) {
    return InstanceRegistry::getInstance().getRegistry().beginUsing(id, result);
}

std::shared_lock<std::shared_mutex> rendell::beginUsingGC(InstanceId id,
                                                          GarbageCollector *&result) {
    Instance *instance;
    auto lock = InstanceRegistry::getInstance().getRegistry().beginUsing(id, instance);
    result = instance ? &instance->getGarbageCollector() : nullptr;
    return lock;
}
} // namespace rendell