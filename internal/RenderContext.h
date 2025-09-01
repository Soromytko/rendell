#pragma once
#include "Buffers/ByteBuffer.h"
#include "DrawCallState.h"
#include "config.h"
#include "raii.h"
#include <rendell/IRenderContext.h>

#include <memory>

namespace rendell {
class RenderContext final : public IRenderContext {
public:
    RenderContext() = default;
    ~RenderContext() = default;

    void setClearBits(bitfield bits) override;
    void setClearColor(float r, float g, float b, float a) override;
    void setClearColor(Color color) override;
    void setViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) override;
    void setScissors(uint32_t x, uint32_t y, uint32_t width, uint32_t height) override;
    void setDrawType(DrawMode drawMode, PrimitiveTopology primitiveTopology,
                     uint32_t instanceCount = 0) override;

    void setShaderProgram(ShaderProgramId shaderProgramId) override;
    void setVertexAssembly(VertexAssemblyId vertexAssemblyId) override;
    void setShaderBuffer(ShaderBufferId shaderBufferId, uint32_t binding) override;
    void setUniformBuffer(UniformBufferId uniformBufferId, uint32_t binding) override;
    void setUniform(UniformInt1Id uniformId, int val) override;
    void setUniform(UniformInt2Id uniformId, int val1, int val2) override;
    void setUniform(UniformInt3Id uniformId, int val1, int val2, int val3) override;
    void setUniform(UniformInt4Id uniformId, int val1, int val2, int val3, int val4) override;
    void setUniform(UniformFloat1Id uniformId, float val1) override;
    void setUniform(UniformFloat2Id uniformId, float val1, float val2) override;
    void setUniform(UniformFloat3Id uniformId, float val1, float val2, float val3) override;
    void setUniform(UniformFloat4Id uniformId, float val1, float val2, float val3,
                    float val4) override;
    void setUniform(UniformMat4Id uniformId, const float *data) override;

    void setTexture2D(UniformSampler2DId uniformSamplerId, Texture2DId textureId,
                      uint32_t stage) override;
    void setTexture2D(UniformSampler2DId uniformSamplerId, Texture2DArrayId textureId,
                      uint32_t stage) override;

    void submit() override;
    void submit(ShaderProgramId shaderProgramId) override;
    void submit(DrawMode drawMode, PrimitiveTopology primitiveTopology) override;

    const DrawCallStateList &getDrawCallStateList() const;
    const ByteBuffer &getUniformBuffer() const;
    const ByteBuffer &getCommandBuffer() const;

    void reset();

private:
    DrawCallStateList _drawCallStates{config::drawCallStateListCapacity};
    DrawCallState _currentDrawCallState{};
    ByteBuffer _commandBuffer{config::renderCommandBufferSize};
    ByteBuffer _uniformBuffer{config::uniformBufferSize};
};

RENDELL_USE_RAII_FACTORY(RenderContext)
} // namespace rendell