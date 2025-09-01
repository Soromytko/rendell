#include <ResourceIdStorage.h>

namespace rendell {
static ResourceIdStorage<IndexBufferId> s_indexBufferIdStorage;
static ResourceIdStorage<VertexBufferId> s_vertexBufferIdStorage;
static ResourceIdStorage<UniformBufferId> s_uniformBufferIdStorage;
static ResourceIdStorage<ShaderBufferId> s_shaderBufferIdStorage;
static ResourceIdStorage<VertexAssemblyId> s_vertexAssemblyIdStorage;
static ResourceIdStorage<Texture2DId> s_texture2DIdStorage;
static ResourceIdStorage<Texture2DArrayId> s_texture2DArrayIdStorage;
static ResourceIdStorage<VertexShaderId> s_vertexShaderIdStorage;
static ResourceIdStorage<FragmentShaderId> s_fragmentShaderIdStorage;
static ResourceIdStorage<ShaderProgramId> s_shaderProgramIdStorage;
static ResourceIdStorage<UniformId> s_uniformIdStorage;
} // namespace rendell

namespace rendell {

ResourceIdStorage<IndexBufferId> &getIndexBufferIdStorage() {
    return s_indexBufferIdStorage;
}

ResourceIdStorage<VertexBufferId> &getVertexBufferIdStorage() {
    return s_vertexBufferIdStorage;
}

ResourceIdStorage<UniformBufferId> &getUniformBufferIdStorage() {
    return s_uniformBufferIdStorage;
}

ResourceIdStorage<ShaderBufferId> &getShaderBufferIdStorage() {
    return s_shaderBufferIdStorage;
}

ResourceIdStorage<VertexAssemblyId> &getVertexAssemblyIdStorage() {
    return s_vertexAssemblyIdStorage;
}

ResourceIdStorage<Texture2DId> &getTexture2DIdStorage() {
    return s_texture2DIdStorage;
}

ResourceIdStorage<Texture2DArrayId> &getTexture2DArrayIdStorage() {
    return s_texture2DArrayIdStorage;
}

ResourceIdStorage<VertexShaderId> &getVertexShaderIdStorage() {
    return s_vertexShaderIdStorage;
}

ResourceIdStorage<FragmentShaderId> &getFragmentShaderIdStorage() {
    return s_fragmentShaderIdStorage;
}

ResourceIdStorage<ShaderProgramId> &getShaderProgramIdStorage() {
    return s_shaderProgramIdStorage;
}

ResourceIdStorage<UniformId> &getUniformIdStorage() {
    return s_uniformIdStorage;
}
} // namespace rendell
