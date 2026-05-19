#pragma once
#pragma once
#pragma once
#include <rendell/ResourceId.h>

#include <cstddef>

namespace rendell {
class ResourceCommandBuffer;

class GarbageCollector final {
public:
    GarbageCollector(size_t lockFreeCapacity);
    ~GarbageCollector() = default;

    GarbageCollector(const GarbageCollector &) = delete;
    GarbageCollector(GarbageCollector &&) = delete;
    GarbageCollector &operator=(const GarbageCollector &) = delete;
    GarbageCollector &operator=(GarbageCollector &&) = delete;

    void collect(ResourceCommandBuffer &buffer);

    void enqueueDestroy(IndexBufferId id);
    void enqueueDestroy(VertexBufferId id);
    void enqueueDestroy(UniformBufferId id);
    void enqueueDestroy(ShaderBufferId id);
    void enqueueDestroy(VertexAssemblyId id);
    void enqueueDestroy(Texture2DId id);
    void enqueueDestroy(Texture2DArrayId id);
    void enqueueDestroy(VertexShaderId id);
    void enqueueDestroy(FragmentShaderId id);
    void enqueueDestroy(ShaderProgramId id);
    void enqueueDestroy(UniformId id);

private:
    static constexpr size_t _implSize = 4352;
    static constexpr size_t _implAlign = 64;
    alignas(_implAlign) std::byte _implStorage[_implSize];
};
} // namespace rendell