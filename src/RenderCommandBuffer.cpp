#include <rendell/RenderCommandBuffer.h>

#include "Command.h"
#include <RenderCommandBufferImpl.h>
#include <rendell/DataType.h>

#include <cassert>

#define IMPL getImpl(_implStorage)

namespace rendell {
static RenderCommandBufferImpl &getImpl(std::byte *storage) {
    return RenderCommandBufferImpl::getFromStorage(storage);
}

RenderCommandBuffer::RenderCommandBuffer() {
    static_assert(sizeof(RenderCommandBufferImpl) == _implSize, "ImplSize is not equal!");
    static_assert(alignof(RenderCommandBufferImpl) == _implAlign, "ImplAlign in not equal!");

    new (_implStorage) RenderCommandBufferImpl();
}

RenderCommandBuffer::~RenderCommandBuffer() {
    IMPL.~RenderCommandBufferImpl();
}

void RenderCommandBuffer::setClearBits(bitfield bits) {
    IMPL.currentDrawCallState.clearBits = bits;
}

void RenderCommandBuffer::setClearColor(float r, float g, float b, float a) {
    setClearColor({r, g, b, a});
}

void RenderCommandBuffer::setClearColor(Color color) {
    ClearColorCmdData cmdData;
    cmdData.r = color.r;
    cmdData.g = color.g;
    cmdData.b = color.b;
    cmdData.a = color.a;
    IMPL.commandBuffer << cmdData.type << cmdData;
}

void RenderCommandBuffer::setViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) {
    SetViewportCmdData cmdData;
    cmdData.x = x;
    cmdData.y = y;
    cmdData.width = width;
    cmdData.height = height;
    IMPL.commandBuffer << cmdData.type << cmdData;
}

void RenderCommandBuffer::setScissors(uint32_t x, uint32_t y, uint32_t width, uint32_t height) {
    SetScissorsCmdData cmdData;
    cmdData.x = x;
    cmdData.y = y;
    cmdData.width = width;
    cmdData.height = height;
    IMPL.commandBuffer << cmdData.type << cmdData;
}

void RenderCommandBuffer::setVertexCount(uint32_t vertexCount) {
    IMPL.currentDrawCallState.vertexCount = vertexCount;
}

void RenderCommandBuffer::setDrawType(DrawMode drawMode, PrimitiveTopology primitiveTopology,
                                      uint32_t instanceCount) {
    IMPL.currentDrawCallState.drawMode = drawMode;
    IMPL.currentDrawCallState.primitiveTopology = primitiveTopology;
    IMPL.currentDrawCallState.instanceCount = instanceCount;
}

void RenderCommandBuffer::setShaderProgram(ShaderProgramId shaderProgramId) {
    assert(shaderProgramId.isValid());
    IMPL.currentDrawCallState.shaderProgramId = shaderProgramId;
}

void RenderCommandBuffer::setVertexAssembly(VertexAssemblyId vertexAssemblyId) {
    assert(vertexAssemblyId.isValid());
    IMPL.currentDrawCallState.vertexAssemblyId = vertexAssemblyId;
}

void RenderCommandBuffer::setShaderBuffer(ShaderBufferId shaderBufferId, uint32_t binding) {
    assert(shaderBufferId.isValid());
    UseShaderBufferCmdData cmdData;
    cmdData.id = shaderBufferId;
    cmdData.binding = binding;
    IMPL.commandBuffer << cmdData.type << cmdData;
}

void RenderCommandBuffer::setUniformBuffer(UniformBufferId uniformBufferId, uint32_t binding) {
    assert(uniformBufferId.isValid());
    UseUniformBufferCmdData cmdData;
    cmdData.id = uniformBufferId;
    cmdData.binding = binding;
    IMPL.commandBuffer << cmdData.type << cmdData;
}

void RenderCommandBuffer::setUniform(UniformInt1Id uniformId, int val) {
    assert(uniformId.isValid());
    IMPL.uniformBuffer << UniformType::int1 << static_cast<UniformId>(uniformId) << val;
}

void RenderCommandBuffer::setUniform(UniformInt2Id uniformId, int val1, int val2) {
    assert(uniformId.isValid());
    IMPL.uniformBuffer << UniformType::int2 << static_cast<UniformId>(uniformId) << val1 << val2;
}

void RenderCommandBuffer::setUniform(UniformInt3Id uniformId, int val1, int val2, int val3) {
    assert(uniformId.isValid());
    IMPL.uniformBuffer << UniformType::int3 << static_cast<UniformId>(uniformId) << val1 << val2
                       << val3;
}

void RenderCommandBuffer::setUniform(UniformInt4Id uniformId, int val1, int val2, int val3,
                                     int val4) {
    assert(uniformId.isValid());
    IMPL.uniformBuffer << UniformType::int4 << static_cast<UniformId>(uniformId) << val1 << val2
                       << val3 << val4;
}

void RenderCommandBuffer::setUniform(UniformFloat1Id uniformId, float val1) {
    assert(uniformId.isValid());
    IMPL.uniformBuffer << UniformType::float1 << static_cast<UniformId>(uniformId) << val1;
}

void RenderCommandBuffer::setUniform(UniformFloat2Id uniformId, float val1, float val2) {
    assert(uniformId.isValid());
    IMPL.uniformBuffer << UniformType::float2 << static_cast<UniformId>(uniformId) << val1 << val2;
}

void RenderCommandBuffer::setUniform(UniformFloat3Id uniformId, float val1, float val2,
                                     float val3) {
    assert(uniformId.isValid());
    IMPL.uniformBuffer << UniformType::float3 << static_cast<UniformId>(uniformId) << val1 << val2
                       << val3;
}

void RenderCommandBuffer::setUniform(UniformFloat4Id uniformId, float val1, float val2, float val3,
                                     float val4) {
    assert(uniformId.isValid());
    IMPL.uniformBuffer << UniformType::float4 << static_cast<UniformId>(uniformId) << val1 << val2
                       << val3 << val4;
}

void RenderCommandBuffer::setUniform(UniformMat4Id uniformId, const float *data) {
    assert(uniformId.isValid());
    IMPL.uniformBuffer << UniformType::mat4 << uniformId;
    IMPL.uniformBuffer.write(reinterpret_cast<const std::byte *>(data), 16 * sizeof(float));
}

void RenderCommandBuffer::setTexture2D(UniformSampler2DId uniformSamplerId, Texture2DId textureId,
                                       uint32_t stage) {
    assert(uniformSamplerId.isValid());
    assert(textureId.isValid());

    SetTexture2DCmdData cmdData;
    cmdData.samplerId = uniformSamplerId;
    cmdData.textureId = textureId;
    cmdData.stage = stage;
    IMPL.commandBuffer << cmdData.type << cmdData;
}

void RenderCommandBuffer::setTexture2D(UniformSampler2DId uniformSamplerId,
                                       Texture2DArrayId textureId, uint32_t stage) {
    assert(uniformSamplerId.isValid());
    assert(textureId.isValid());

    SetTexture2DArrayCmdData cmdData;
    cmdData.samplerId = uniformSamplerId;
    cmdData.textureId = textureId;
    cmdData.stage = stage;
    IMPL.commandBuffer << cmdData.type << cmdData;
}

void RenderCommandBuffer::submit() {
    auto &drawCallState = IMPL.currentDrawCallState;
    auto &drawCallStates = IMPL.drawCallStates;
    auto &commandBuffer = IMPL.commandBuffer;
    auto &uniformBuffer = IMPL.uniformBuffer;

    drawCallState.commandBufferSize = commandBuffer.getSize() - drawCallState.commandBufferOffset;
    drawCallState.uniformBufferSize = uniformBuffer.getSize() - drawCallState.uniformBufferOffset;

    drawCallStates.append(drawCallState);

    drawCallState.reset();
    drawCallState.commandBufferOffset = commandBuffer.getSize();
    drawCallState.uniformBufferOffset = uniformBuffer.getSize();
}

void RenderCommandBuffer::submit(ShaderProgramId shaderProgramId) {
    IMPL.currentDrawCallState.shaderProgramId = shaderProgramId;
    submit();
}

void RenderCommandBuffer::submit(DrawMode drawMode, PrimitiveTopology primitiveTopology) {
    setDrawType(drawMode, primitiveTopology);
    submit();
}
} // namespace rendell