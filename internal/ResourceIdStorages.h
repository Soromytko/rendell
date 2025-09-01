#pragma once
#include "ResourceIdStorage.h"
#include <rendell/ResourceId.h>

namespace rendell {
ResourceIdStorage<IndexBufferId> &getIndexBufferIdStorage();
ResourceIdStorage<VertexBufferId> &getVertexBufferIdStorage();
ResourceIdStorage<UniformBufferId> &getUniformBufferIdStorage();
ResourceIdStorage<ShaderBufferId> &getShaderBufferIdStorage();
ResourceIdStorage<VertexAssemblyId> &getVertexAssemblyIdStorage();
ResourceIdStorage<Texture2DId> &getTexture2DIdStorage();
ResourceIdStorage<Texture2DArrayId> &getTexture2DArrayIdStorage();
ResourceIdStorage<VertexShaderId> &getVertexShaderIdStorage();
ResourceIdStorage<FragmentShaderId> &getFragmentShaderIdStorage();
ResourceIdStorage<ShaderProgramId> &getShaderProgramIdStorage();
ResourceIdStorage<UniformId> &getUniformIdStorage();
} // namespace rendell
