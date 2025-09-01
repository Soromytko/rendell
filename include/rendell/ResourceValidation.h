#pragma once
#include "ResourceId.h"

namespace rendell {
bool isValid(IndexBufferId indexBufferId);
bool isValid(VertexBufferId vertexBufferId);
bool isValid(UniformBufferId uniformBufferId);
bool isValid(ShaderBufferId shaderBufferId);
bool isValid(VertexAssemblyId vertexAssemblyId);
bool isValid(Texture2DId texture2DId);
bool isValid(Texture2DArrayId texture2DArrayId);
bool isValid(VertexShaderId vertexShaderId);
bool isValid(FragmentShaderId fragmentShaderId);
bool isValid(ShaderProgramId shaderProgramId);
bool isValid(UniformId uniformId);
} // namespace rendell