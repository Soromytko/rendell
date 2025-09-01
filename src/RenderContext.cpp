#include <rendell/RenderContext.h>

#include <Command.h>
#include <CommandBuffer.h>
#include <DrawCallState.h>
#include <RenderContextImpl.h>
#include <ResourceIdStorage.h>

#include <utility>

#define TO_BYTES(v) reinterpret_cast<const uint8_t *>(&v)

namespace rendell {
static ResourceIdStorage<IndexBufferId> s_indexBufferIdStorage;
static ResourceIdStorage<VertexBufferId> s_vertexBufferIdStorage;
static ResourceIdStorage<VertexArrayBufferId> s_vertexArrayBufferIdStorage;
static ResourceIdStorage<Texture2DId> s_texture2DIdStorage;
static ResourceIdStorage<Texture2DArrayId> s_texture2DArrayIdStorage;
static ResourceIdStorage<VertexShaderId> s_vertexShaderIdStorage;
static ResourceIdStorage<FragmentShaderId> s_fragmentShaderIdStorage;
static ResourceIdStorage<ShaderProgramId> s_shaderProgramIdStorage;
static ResourceIdStorage<UniformId> s_uniformIdStorage;
} // namespace rendell

namespace rendell {
CommandBufferPairSharedPtr RenderContext::Impl::getCurrentCommandBufferPair() {
    if (currentCommandBufferPair == firstCommandBufferPair.get()) {
        return firstCommandBufferPair;
    }
    return secondCommandBufferPair;
}

void RenderContext::Impl::swapCommandBufferPair() {
    if (currentCommandBufferPair == firstCommandBufferPair.get()) {
        currentCommandBufferPair = secondCommandBufferPair.get();
    } else {
        currentCommandBufferPair = firstCommandBufferPair.get();
    }
}

void RenderContext::Impl::submit() {
    if (drawCallStates.size() >= drawCallCount) {
        drawCallStates.push_back(currentDrawCallState);
        drawCallCount++;
    } else {
        drawCallStates[drawCallCount++] = currentDrawCallState;
    }
    currentDrawCallState.reset();
}

RenderContext::RenderContext() {
    _impl = std::make_unique<RenderContext::Impl>();
    _impl->firstCommandBufferPair = std::make_shared<CommandBufferPair>();
    _impl->secondCommandBufferPair = std::make_shared<CommandBufferPair>();
}

void writeCommand(CommandBuffer *commandBuffer, CmdType type, const uint8_t *data, size_t size) {
    const auto rawBufferId = commandBuffer->startRawWriting();
    // TODO: Check result!
    commandBuffer->writeRaw(rawBufferId, TO_BYTES(type), sizeof(type));
    commandBuffer->writeRaw(rawBufferId, data, size);

    if (std::this_thread::get_id() == s_mainThreadId) {
        // Execute the commands until the space is free.
        while (!commandBuffer->commitRawWriting(rawBufferId)) {
            // execute command
        }
    } else {
        // Make the thread wait.
        while (!commandBuffer->commitRawWriting(rawBufferId))
            ;
    }
}

bool readCmdType(CommandBuffer &commandBuffer, CmdType &type) {
    CommandBuffer::data_t *dataSource = reinterpret_cast<CommandBuffer::data_t *>(&type);
    return commandBuffer.read(dataSource, sizeof(CmdType));
}

template <typename T> bool readCmdData(CommandBuffer &commandBuffer, T &commandData) {
    CommandBuffer::data_t *dataSource = reinterpret_cast<CommandBuffer::data_t *>(&commandData);
    while (!commandBuffer.read(dataSource, sizeof(T)))
        ;
}

#define PREPARE_COMMAND_BUFFER _impl->getCurrentCommandBufferPair()->prepareCommandBuffer.get()

IndexBufferId RenderContext::createIndexBuffer(const IndexBufferData &data) {
    IndexBufferId id = s_indexBufferIdStorage.alloc();
    CreateIndexBufferCmdData cmdData;
    cmdData.id = id;
    cmdData.data = AllocArray(data.data(), data.size());
    writeCommand(PREPARE_COMMAND_BUFFER, cmdData.type, TO_BYTES(cmdData), sizeof(cmdData));
    return id;
}

VertexBufferId RenderContext::createVertexBuffer(const VertexBufferData &data) {
    VertexBufferId id = s_vertexBufferIdStorage.alloc();
    CreateVertexBufferCmdData cmdData;
    cmdData.id = id;
    cmdData.data = AllocArray(data.data(), data.size());
    writeCommand(PREPARE_COMMAND_BUFFER, cmdData.type, TO_BYTES(cmdData), sizeof(cmdData));
    return id;
}

VertexArrayBufferId
RenderContext::createVertexArrayBuffer(IndexBufferId indexBufferId,
                                       std::initializer_list<VertexBufferId> vertexBuffers) {
    VertexArrayBufferId id = s_vertexArrayBufferIdStorage.alloc();
    CreateVertexArrayBufferCmdData cmdData;
    cmdData.id = id;
    cmdData.indexBufferId = indexBufferId;
    cmdData.vertexBuffers = AllocArray(vertexBuffers.begin(), vertexBuffers.size());
    writeCommand(PREPARE_COMMAND_BUFFER, cmdData.type, TO_BYTES(cmdData), sizeof(cmdData));
    return id;
}

Texture2DId RenderContext::createTexture2D() {
    Texture2DId id = s_texture2DIdStorage.alloc();
    CreateTexture2DCmdData cmdData;
    writeCommand(PREPARE_COMMAND_BUFFER, cmdData.type, TO_BYTES(cmdData), sizeof(cmdData));
    return id;
}

Texture2DArrayId RenderContext::createTexture2DArray() {
    Texture2DArrayId id = s_texture2DArrayIdStorage.alloc();
    CreateTexture2DArrayCmdData cmdData;
    writeCommand(PREPARE_COMMAND_BUFFER, cmdData.type, TO_BYTES(cmdData), sizeof(cmdData));
    return id;
}

VertexShaderId RenderContext::createVertexShader(const std::string &src) {
    VertexShaderId id = s_vertexShaderIdStorage.alloc();
    CreateVertexShaderCmdData cmdData;
    cmdData.id = id;
    cmdData.src = AllocArray(src.data(), src.size());
    writeCommand(PREPARE_COMMAND_BUFFER, cmdData.type, TO_BYTES(cmdData), sizeof(cmdData));
    return id;
}

FragmentShaderId RenderContext::createFragmentShader(const std::string &src) {
    FragmentShaderId id = s_fragmentShaderIdStorage.alloc();
    CreateFragmentShaderCmdData cmdData;
    cmdData.id = id;
    cmdData.src = AllocArray(src.data(), src.size());
    writeCommand(PREPARE_COMMAND_BUFFER, cmdData.type, TO_BYTES(cmdData), sizeof(cmdData));
    return id;
}

ShaderProgramId RenderContext::createShaderProgram(VertexShaderId vertexShaderId,
                                                   FragmentShaderId fragmentShaderId) {
    ShaderProgramId id = s_shaderProgramIdStorage.alloc();
    CreateShaderProgramCmdData cmdData;
    cmdData.id = id;
    cmdData.vertexShaderId = vertexShaderId;
    cmdData.fragmentShaderId = fragmentShaderId;
    writeCommand(PREPARE_COMMAND_BUFFER, cmdData.type, TO_BYTES(cmdData), sizeof(cmdData));
    return id;
}

UniformId RenderContext::createUniform(const std::string &name, UniformType type) {
    UniformId id = s_uniformIdStorage.alloc();
    CreateUniformCmdData cmdData;
    cmdData.id = id;
    cmdData.dataType = type;
    writeCommand(PREPARE_COMMAND_BUFFER, cmdData.type, TO_BYTES(cmdData), sizeof(cmdData));
}

void RenderContext::setShaderProgram(ShaderProgramId shaderProgram) {
    _impl->currentDrawCallState.shaderProgramId = shaderProgram;
}

void RenderContext::setIndexBuffer(IndexBufferId indexBuffer) {
    //_impl->drawCallState.indexBuffer = indexBuffer;
}

void RenderContext::setVertexArray(VertexArrayBufferId vertexArray) {
    _impl->currentDrawCallState.vertexArrayBuffer = vertexArray;
}

void RenderContext::submit(ShaderProgramId shaderProgram) {
    _impl->currentDrawCallState.shaderProgramId = shaderProgram;
    submit();
}

void RenderContext::submit() {
    _impl->submit();
}

} // namespace rendell
