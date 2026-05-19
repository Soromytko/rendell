#pragma once
#include <rendell/Color.h>
#include <rendell/DataType.h>
#include <rendell/DrawType.h>
#include <rendell/ResourceId.h>

namespace rendell {
class RenderCommandBuffer final {
    friend struct RendellExtractor;

public:
    RenderCommandBuffer();
    ~RenderCommandBuffer();

    RenderCommandBuffer(const RenderCommandBuffer &) = delete;
    RenderCommandBuffer(RenderCommandBuffer &&) = delete;
    RenderCommandBuffer &operator=(const RenderCommandBuffer &) = delete;
    RenderCommandBuffer &operator=(RenderCommandBuffer &&) = delete;

    void setClearBits(bitfield bits);
    void setClearColor(float r, float g, float b, float a);
    void setClearColor(Color color);
    void setViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height);
    void setScissors(uint32_t x, uint32_t y, uint32_t width, uint32_t height);
    void setVertexCount(uint32_t vertexCount);
    void setDrawType(DrawMode drawMode, PrimitiveTopology primitiveTopology,
                     uint32_t instanceCount = 0);

    void setShaderProgram(ShaderProgramId shaderProgramId);
    void setVertexAssembly(VertexAssemblyId vertexAssemblyId);
    void setShaderBuffer(ShaderBufferId shaderBufferId, uint32_t binding);
    void setUniformBuffer(UniformBufferId uniformBufferId, uint32_t binding);
    void setUniform(UniformInt1Id uniformId, int val);
    void setUniform(UniformInt2Id uniformId, int val1, int val2);
    void setUniform(UniformInt3Id uniformId, int val1, int val2, int val3);
    void setUniform(UniformInt4Id uniformId, int val1, int val2, int val3, int val4);
    void setUniform(UniformFloat1Id uniformId, float val1);
    void setUniform(UniformFloat2Id uniformId, float val1, float val2);
    void setUniform(UniformFloat3Id uniformId, float val1, float val2, float val3);
    void setUniform(UniformFloat4Id uniformId, float val1, float val2, float val3, float val4);
    void setUniform(UniformMat4Id uniformId, const float *data);

    void setTexture2D(UniformSampler2DId uniformSamplerId, Texture2DId textureId, uint32_t stage);
    void setTexture2D(UniformSampler2DId uniformSamplerId, Texture2DArrayId textureId,
                      uint32_t stage);
    
    void submit();
    void submit(ShaderProgramId shaderProgramId);
    void submit(DrawMode drawMode, PrimitiveTopology primitiveTopology);

private:
    static constexpr size_t _implSize = 232;
    static constexpr size_t _implAlign = 8;
    alignas(_implAlign) std::byte _implStorage[_implSize];
};
} // namespace rendell