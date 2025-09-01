#include <rendell/ResourceValidation.h>

#include <ResourceIdStorages.h>

namespace rendell {
bool isValid(IndexBufferId indexBufferId) {
    return getIndexBufferIdStorage().isValid(indexBufferId);
}

bool isValid(VertexBufferId vertexBufferId) {
    return getVertexBufferIdStorage().isValid(vertexBufferId);
}

bool isValid(UniformBufferId uniformBufferId) {
    return getUniformBufferIdStorage().isValid(uniformBufferId);
}

bool isValid(ShaderBufferId shaderBufferId) {
    return getShaderBufferIdStorage().isValid(shaderBufferId);
}

bool isValid(VertexAssemblyId vertexAssemblyId) {
    return getVertexAssemblyIdStorage().isValid(vertexAssemblyId);
}

bool isValid(Texture2DId texture2DId) {
    return getTexture2DIdStorage().isValid(texture2DId);
}

bool isValid(Texture2DArrayId texture2DArrayId) {
    return getTexture2DArrayIdStorage().isValid(texture2DArrayId);
}

bool isValid(VertexShaderId vertexShaderId) {
    return getVertexShaderIdStorage().isValid(vertexShaderId);
}

bool isValid(FragmentShaderId fragmentShaderId) {
    return getFragmentShaderIdStorage().isValid(fragmentShaderId);
}

bool isValid(ShaderProgramId shaderProgramId) {
    return getShaderProgramIdStorage().isValid(shaderProgramId);
}

bool isValid(UniformId uniformId) {
    return getUniformIdStorage().isValid(uniformId);
}
} // namespace rendell