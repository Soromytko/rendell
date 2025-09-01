#include <rendell/hash.h>

#include <typeinfo>

namespace rendell {
static size_t hashResourceId(ResourceId resourceId, const std::type_info &info) noexcept {
    std::size_t h1 = (static_cast<std::size_t>(resourceId.index) << 16) | resourceId.version;
    std::size_t h2 = reinterpret_cast<std::size_t>(&info);
    return h1 ^ (h2 + 0x9e3779b97f4a7c15ULL + (h1 << 6) + (h1 >> 2));
}

template <typename TResourceId>
inline static size_t hashResourceId(TResourceId resourceId) noexcept {
    return hashResourceId(static_cast<ResourceId>(resourceId), typeid(TResourceId));
}

size_t hash(IndexBufferId indexBufferId) {
    return hashResourceId(indexBufferId);
}

size_t hash(VertexBufferId vertexBufferId) {
    return hashResourceId(vertexBufferId);
}

size_t hash(VertexAssemblyId vertexAssemblyId) {
    return hashResourceId(vertexAssemblyId);
}

size_t hash(ShaderBufferId shaderBufferId) {
    return hashResourceId(shaderBufferId);
}

size_t hash(Texture2DId texture2DId) {
    return hashResourceId(texture2DId);
}

size_t hash(Texture2DArrayId texture2DArrayId) {
    return hashResourceId(texture2DArrayId);
}

size_t hash(UniformBufferId uniformBufferId) {
    return hashResourceId(uniformBufferId);
}

size_t hash(VertexShaderId vertexShaderId) {
    return hashResourceId(vertexShaderId);
}

size_t hash(FragmentShaderId fragmentShaderId) {
    return hashResourceId(fragmentShaderId);
}

size_t hash(ShaderProgramId shaderProgramId) {
    return hashResourceId(shaderProgramId);
}

size_t hash(DynamicIndexBufferId dynamicIndexBufferId) {
    return hashResourceId(dynamicIndexBufferId);
}

size_t hash(DynamicVertexBufferId dynamicVertexBufferId) {
    return hashResourceId(dynamicVertexBufferId);
}

size_t hash(UniformId uniformId) {
    return hashResourceId(uniformId);
}
} // namespace rendell