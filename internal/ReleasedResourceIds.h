#pragma once
#include <Buffers/RingBuffer.h>
#include <rendell/ResourceId.h>

#include <cassert>

namespace rendell {
struct ReleasedResourceIds {
    RingBuffer<IndexBufferId> indexBufferIds;
    RingBuffer<VertexBufferId> vertexBufferIds;
    RingBuffer<VertexAssemblyId> vertexAssemblyIds;
    RingBuffer<ShaderBufferId> shaderBufferIds;
    RingBuffer<Texture2DId> texture2DIds;
    RingBuffer<Texture2DArrayId> texture2DArrayIds;
    RingBuffer<UniformBufferId> uniformBufferIds;
    RingBuffer<VertexShaderId> vertexShaderIds;
    RingBuffer<FragmentShaderId> fragmentShaderIds;
    RingBuffer<ShaderProgramId> shaderProgramIds;
    RingBuffer<UniformId> uniformIds;

    explicit ReleasedResourceIds(size_t capacity)
        : indexBufferIds(capacity)
        , vertexBufferIds(capacity)
        , vertexAssemblyIds(capacity)
        , shaderBufferIds(capacity)
        , texture2DIds(capacity)
        , texture2DArrayIds(capacity)
        , uniformBufferIds(capacity)
        , vertexShaderIds(capacity)
        , fragmentShaderIds(capacity)
        , shaderProgramIds(capacity)
        , uniformIds(capacity) {
        assert(capacity > 0);
    }

    bool isEmpty() const noexcept {
        return indexBufferIds.isEmpty() && vertexBufferIds.isEmpty() &&
               vertexAssemblyIds.isEmpty() && shaderBufferIds.isEmpty() && texture2DIds.isEmpty() &&
               texture2DArrayIds.isEmpty() && uniformBufferIds.isEmpty() &&
               vertexShaderIds.isEmpty() && fragmentShaderIds.isEmpty() &&
               shaderProgramIds.isEmpty() && uniformIds.isEmpty();
    }

    void reset() noexcept {
        indexBufferIds.reset();
        vertexBufferIds.reset();
        vertexAssemblyIds.reset();
        shaderBufferIds.reset();
        texture2DIds.reset();
        texture2DArrayIds.reset();
        uniformBufferIds.reset();
        vertexShaderIds.reset();
        fragmentShaderIds.reset();
        shaderProgramIds.reset();
        uniformIds.reset();
    }
};

} // namespace rendell