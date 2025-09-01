#pragma once
#include "ResourceId.h"

#include <cstddef>

namespace rendell {
struct ResourceIdHash {
    template <typename T> std::size_t operator()(const T &resourceId) const noexcept {
        static_assert(std::is_base_of_v<ResourceId, T>, "T must derive from ResourceId");
        return hash(resourceId);
    }
};

size_t hash(IndexBufferId indexBufferId);
size_t hash(VertexBufferId vertexBufferId);
size_t hash(VertexAssemblyId vertexAssemblyId);
size_t hash(ShaderBufferId shaderBufferId);
size_t hash(Texture2DId texture2DId);
size_t hash(Texture2DArrayId texture2DArrayId);
size_t hash(UniformBufferId uniformBufferId);
size_t hash(VertexShaderId vertexShaderId);
size_t hash(FragmentShaderId fragmentShaderId);
size_t hash(ShaderProgramId shaderProgramId);
size_t hash(DynamicIndexBufferId dynamicIndexBufferId);
size_t hash(DynamicVertexBufferId dynamicVertexBufferId);
size_t hash(UniformId uniformId);
} // namespace rendell