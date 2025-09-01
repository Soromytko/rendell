#pragma once
#include "DataType.h"
#include "DrawType.h"
#include "ResourceId.h"

namespace rendell {
class IRenderContext {
public:
    IRenderContext() = default;
    ~IRenderContext() = default;

    virtual void setClearBits(bitfield bits) = 0;
    virtual void setClearColor(float r, float g, float b, float a) = 0;
    virtual void setClearColor(Color color) = 0;
    virtual void setViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) = 0;
    virtual void setScissors(uint32_t x, uint32_t y, uint32_t width, uint32_t height) = 0;
    virtual void setDrawType(DrawMode drawMode, PrimitiveTopology primitiveTopology,
                             uint32_t instanceCount = 0) = 0;

    virtual void setShaderProgram(ShaderProgramId shaderProgramId) = 0;
    virtual void setVertexAssembly(VertexAssemblyId vertexAssemblyId) = 0;
    virtual void setShaderBuffer(ShaderBufferId shaderBufferId, uint32_t binding) = 0;
    virtual void setUniformBuffer(UniformBufferId uniformBufferId, uint32_t binding) = 0;
    virtual void setUniform(UniformInt1Id uniformId, int val) = 0;
    virtual void setUniform(UniformInt2Id uniformId, int val1, int val2) = 0;
    virtual void setUniform(UniformInt3Id uniformId, int val1, int val2, int val3) = 0;
    virtual void setUniform(UniformInt4Id uniformId, int val1, int val2, int val3, int val4) = 0;
    virtual void setUniform(UniformFloat1Id uniformId, float val1) = 0;
    virtual void setUniform(UniformFloat2Id uniformId, float val1, float val2) = 0;
    virtual void setUniform(UniformFloat3Id uniformId, float val1, float val2, float val3) = 0;
    virtual void setUniform(UniformFloat4Id uniformId, float val1, float val2, float val3,
                            float val4) = 0;
    virtual void setUniform(UniformMat4Id uniformId, const float *data) = 0;

    virtual void setTexture2D(UniformSampler2DId uniformSamplerId, Texture2DId textureId,
                              uint32_t stage) = 0;
    virtual void setTexture2D(UniformSampler2DId uniformSamplerId, Texture2DArrayId textureId,
                              uint32_t stage) = 0;

    virtual void submit() = 0;
    virtual void submit(ShaderProgramId shaderProgramId) = 0;
    virtual void submit(DrawMode drawMode, PrimitiveTopology primitiveTopology) = 0;
};
} // namespace rendell