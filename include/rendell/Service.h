#pragma once
#include <rendell/ResourceId.h>

#include <shared_mutex>

namespace rendell {
class Instance;
class GarbageCollector;

[[nodiscard]] std::shared_lock<std::shared_mutex> beginUsingInstance(InstanceId id,
                                                                     Instance *&result);
[[nodiscard]] std::shared_lock<std::shared_mutex> beginUsingGC(InstanceId id,
                                                               GarbageCollector *&result);
} // namespace rendell