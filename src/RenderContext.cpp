#include "RenderContext.h"

#include "Command.h"
#include <rendell/DataType.h>
#include <rendell/ResourceValidation.h>

#include <cassert>

namespace rendell {
void RenderContext::setClearBits(bitfield bits) {
    _currentDrawCallState.clearBits = bits;
}

void RenderContext::setClearColor(float r, float g, float b, float a) {
    setClearColor({r, g, b, a});
}

void RenderContext::setClearColor(Color color) {
    ClearColorCmdData cmdData;
    cmdData.r = color.r;
    cmdData.g = color.g;
    cmdData.b = color.b;
    cmdData.a = color.a;
    _commandBuffer << cmdData.type << cmdData;
}

void RenderContext::setViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) {
    SetViewportCmdData cmdData;
    cmdData.x = x;
    cmdData.y = y;
    cmdData.width = width;
    cmdData.height = height;
    _commandBuffer << cmdData.type << cmdData;
}

void RenderContext::setScissors(uint32_t x, uint32_t y, uint32_t width, uint32_t height) {
    SetScissorsCmdData cmdData;
    cmdData.x = x;
    cmdData.y = y;
    cmdData.width = width;
    cmdData.height = height;
    _commandBuffer << cmdData.type << cmdData;
}

void RenderContext::setDrawType(DrawMode drawMode, PrimitiveTopology primitiveTopology,
                                uint32_t instanceCount) {
    _currentDrawCallState.drawMode = drawMode;
    _currentDrawCallState.primitiveTopology = primitiveTopology;
    _currentDrawCallState.instanceCount = instanceCount;
}

void RenderContext::setShaderProgram(ShaderProgramId shaderProgramId) {
    assert(isValid(shaderProgramId));
    _currentDrawCallState.shaderProgramId = shaderProgramId;
}

void RenderContext::setVertexAssembly(VertexAssemblyId vertexAssemblyId) {
    assert(isValid(vertexAssemblyId));
    _currentDrawCallState.vertexAssemblyId = vertexAssemblyId;
}

void RenderContext::setShaderBuffer(ShaderBufferId shaderBufferId, uint32_t binding) {
    assert(isValid(shaderBufferId));
    UseShaderBufferCmdData cmdData;
    cmdData.id = shaderBufferId;
    cmdData.binding = binding;
    _commandBuffer << cmdData.type << cmdData;
}

void RenderContext::setUniformBuffer(UniformBufferId uniformBufferId, uint32_t binding) {
    assert(isValid(uniformBufferId));
    UseUniformBufferCmdData cmdData;
    cmdData.id = uniformBufferId;
    cmdData.binding = binding;
    _commandBuffer << cmdData.type << cmdData;
}

void RenderContext::setUniform(UniformInt1Id uniformId, int val) {
    assert(isValid(uniformId));
    _uniformBuffer << UniformType::int1 << static_cast<UniformId>(uniformId) << val;
}

void RenderContext::setUniform(UniformInt2Id uniformId, int val1, int val2) {
    assert(isValid(uniformId));
    _uniformBuffer << UniformType::int2 << static_cast<UniformId>(uniformId) << val1 << val2;
}

void RenderContext::setUniform(UniformInt3Id uniformId, int val1, int val2, int val3) {
    assert(isValid(uniformId));
    _uniformBuffer << UniformType::int3 << static_cast<UniformId>(uniformId) << val1 << val2
                   << val3;
}

void RenderContext::setUniform(UniformInt4Id uniformId, int val1, int val2, int val3, int val4) {
    assert(isValid(uniformId));
    _uniformBuffer << UniformType::int4 << static_cast<UniformId>(uniformId) << val1 << val2 << val3
                   << val4;
}

void RenderContext::setUniform(UniformFloat1Id uniformId, float val1) {
    assert(isValid(uniformId));
    _uniformBuffer << UniformType::float1 << static_cast<UniformId>(uniformId) << val1;
}

void RenderContext::setUniform(UniformFloat2Id uniformId, float val1, float val2) {
    assert(isValid(uniformId));
    _uniformBuffer << UniformType::float2 << static_cast<UniformId>(uniformId) << val1 << val2;
}

void RenderContext::setUniform(UniformFloat3Id uniformId, float val1, float val2, float val3) {
    _uniformBuffer << UniformType::float3 << static_cast<UniformId>(uniformId) << val1 << val2
                   << val3;
}

void RenderContext::setUniform(UniformFloat4Id uniformId, float val1, float val2, float val3,
                               float val4) {
    assert(isValid(uniformId));
    _uniformBuffer << UniformType::float4 << static_cast<UniformId>(uniformId) << val1 << val2
                   << val3 << val4;
}

void RenderContext::setUniform(UniformMat4Id uniformId, const float *data) {
    assert(isValid(uniformId));
    _uniformBuffer << UniformType::mat4 << uniformId;
    _uniformBuffer.write(reinterpret_cast<const std::byte *>(data), 16 * sizeof(float));
}

void RenderContext::setTexture2D(UniformSampler2DId uniformSamplerId, Texture2DId textureId,
                                 uint32_t stage) {
    assert(isValid(uniformSamplerId));
    assert(isValid(textureId));
    SetTexture2DCmdData cmdData;
    cmdData.samplerId = uniformSamplerId;
    cmdData.textureId = textureId;
    cmdData.stage = stage;
    _commandBuffer << cmdData.type << cmdData;
}

void RenderContext::setTexture2D(UniformSampler2DId uniformSamplerId, Texture2DArrayId textureId,
                                 uint32_t stage) {
    assert(isValid(uniformSamplerId));
    assert(isValid(textureId));
    SetTexture2DArrayCmdData cmdData;
    cmdData.samplerId = uniformSamplerId;
    cmdData.textureId = textureId;
    cmdData.stage = stage;
    _commandBuffer << cmdData.type << cmdData;
}

void RenderContext::submit() {
    _currentDrawCallState.commandBufferSize =
        _commandBuffer.getSize() - _currentDrawCallState.commandBufferOffset;
    _currentDrawCallState.uniformBufferSize =
        _uniformBuffer.getSize() - _currentDrawCallState.uniformBufferOffset;

    _drawCallStates.append(_currentDrawCallState);

    _currentDrawCallState.reset();
    _currentDrawCallState.commandBufferOffset = _commandBuffer.getSize();
    _currentDrawCallState.uniformBufferOffset = _uniformBuffer.getSize();
}

void RenderContext::submit(ShaderProgramId shaderProgramId) {
    _currentDrawCallState.shaderProgramId = shaderProgramId;
    submit();
}

void RenderContext::submit(DrawMode drawMode, PrimitiveTopology primitiveTopology) {
    setDrawType(drawMode, primitiveTopology);
    submit();
}

const DrawCallStateList &RenderContext::getDrawCallStateList() const {
    return _drawCallStates;
}

const ByteBuffer &RenderContext::getUniformBuffer() const {
    return _uniformBuffer;
}

const ByteBuffer &RenderContext::getCommandBuffer() const {
    return _commandBuffer;
}

void RenderContext::reset() {
    _drawCallStates.reset();
    _commandBuffer.reset();
    _uniformBuffer.reset();
    _currentDrawCallState.reset();
}

} // namespace rendell