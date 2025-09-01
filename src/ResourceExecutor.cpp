#include <ResourceExecutor.h>
#include <cassert>

namespace rendell {
void ResourceExecutor::execute(const ByteBuffer &resourceBuffer,
                               ResourceDataProviderSharedPtr resourceDataProvider) {
    _resourceDataProvider = resourceDataProvider;
    ByteBufferReader bufferReader(resourceBuffer);
    while (!bufferReader.isEmpty()) {
        assert(bufferReader.canRead(sizeof(CmdType)));
        const CmdType cmdType = bufferReader.read<CmdType>();
        switch (cmdType) {
        case CmdType::createIndexBufferCmdType: {
            CreateIndexBufferCmdData cmdData;
            assert(bufferReader.canRead(sizeof(cmdData)));
            cmdData = bufferReader.read<decltype(cmdData)>();
            createIndexBuffer(cmdData);
        } break;
        case CmdType::createVertexBufferCmdType: {
            CreateVertexBufferCmdData cmdData;
            assert(bufferReader.canRead(sizeof(cmdData)));
            cmdData = bufferReader.read<decltype(cmdData)>();
            createVertexBuffer(cmdData);
        } break;
        case CmdType::createVertexAssemblyCmdType: {
            CreateVertexAssemblyCmdData cmdData;
            assert(bufferReader.canRead(sizeof(cmdData)));
            cmdData = bufferReader.read<decltype(cmdData)>();
            createVertexAssembly(cmdData);
        } break;
        case CmdType::createShaderBufferCmdType: {
            CreateShaderBufferCmdData cmdData;
            assert(bufferReader.canRead(sizeof(cmdData)));
            cmdData = bufferReader.read<decltype(cmdData)>();
            createShaderBuffer(cmdData);
        } break;
        case CmdType::createTexture2DCmdType: {
            CreateTexture2DCmdData cmdData;
            assert(bufferReader.canRead(sizeof(cmdData)));
            cmdData = bufferReader.read<decltype(cmdData)>();
            createTexture2D(cmdData);
        } break;
        case CmdType::createTexture2DArrayCmdType: {
            CreateTexture2DArrayCmdData cmdData;
            assert(bufferReader.canRead(sizeof(cmdData)));
            cmdData = bufferReader.read<decltype(cmdData)>();
            createTexture2DArray(cmdData);
        } break;
        case CmdType::createUniformBufferCmdType: {
            CreateUniformCmdData cmdData;
            assert(bufferReader.canRead(sizeof(cmdData)));
            cmdData = bufferReader.read<decltype(cmdData)>();
            createUniform(cmdData);
        } break;
        case CmdType::createVertexShaderCmdType: {
            CreateVertexShaderCmdData cmdData;
            assert(bufferReader.canRead(sizeof(cmdData)));
            cmdData = bufferReader.read<decltype(cmdData)>();
            createVertexShader(cmdData);
        } break;
        case CmdType::createFragmentShaderCmdType: {
            CreateFragmentShaderCmdData cmdData;
            assert(bufferReader.canRead(sizeof(cmdData)));
            cmdData = bufferReader.read<decltype(cmdData)>();
            createFragmentShader(cmdData);
        } break;
        case CmdType::createShaderProgramCmdType: {
            CreateShaderProgramCmdData cmdData;
            assert(bufferReader.canRead(sizeof(cmdData)));
            cmdData = bufferReader.read<decltype(cmdData)>();
            createShaderProgram(cmdData);
        } break;
        case CmdType::createUniformCmdType: {
            CreateUniformCmdData cmdData;
            assert(bufferReader.canRead(sizeof(cmdData)));
            cmdData = bufferReader.read<decltype(cmdData)>();
            createUniform(cmdData);
        } break;
        case CmdType::setIndexBufferSubDataCmdType: {
            SetIndexBufferSubDataCmdData cmdData;
            assert(bufferReader.canRead(sizeof(cmdData)));
            cmdData = bufferReader.read<decltype(cmdData)>();
            setIndexBufferSubData(cmdData);
        } break;
        case CmdType::setVertexBufferSubDataCmdType: {
            SetVertexBufferSubDataCmdData cmdData;
            assert(bufferReader.canRead(sizeof(cmdData)));
            cmdData = bufferReader.read<decltype(cmdData)>();
            setVertexBufferSubData(cmdData);
        } break;
        case CmdType::setShaderBufferSubDataCmdType: {
            SetShaderBufferSubDataCmdData cmdData;
            assert(bufferReader.canRead(sizeof(cmdData)));
            cmdData = bufferReader.read<decltype(cmdData)>();
            setShaderBufferSubData(cmdData);
        } break;
        case CmdType::setTexture2DSubDataCmdType: {
            SetTexture2DSubDataCmdData cmdData;
            assert(bufferReader.canRead(sizeof(cmdData)));
            cmdData = bufferReader.read<decltype(cmdData)>();
            setTexture2DSubData(cmdData);
        } break;
        case CmdType::setTexture2DArraySubDataCmdType: {
            SetTexture2DArraySubDataCmdData cmdData;
            assert(bufferReader.canRead(sizeof(cmdData)));
            cmdData = bufferReader.read<decltype(cmdData)>();
            setTexture2DArraySubData(cmdData);
        } break;
        case CmdType::destroyIndexBufferCmdType: {
            DestroyIndexBufferCmdData cmdData;
            assert(bufferReader.canRead(sizeof(cmdData)));
            cmdData = bufferReader.read<decltype(cmdData)>();
            destroyIndexBuffer(cmdData);
        } break;
        case CmdType::destroyVertexBufferCmdType: {
            DestroyVertexBufferCmdData cmdData;
            assert(bufferReader.canRead(sizeof(cmdData)));
            cmdData = bufferReader.read<decltype(cmdData)>();
            destroyVertexBuffer(cmdData);
        } break;
        case CmdType::destroyUniformBufferCmdType: {
            DestroyUniformBufferCmdData cmdData;
            assert(bufferReader.canRead(sizeof(cmdData)));
            cmdData = bufferReader.read<decltype(cmdData)>();
            destroyUniformBuffer(cmdData);
        } break;
        case CmdType::destroyShaderBufferCmdType: {
            DestroyShaderBufferCmdData cmdData;
            assert(bufferReader.canRead(sizeof(cmdData)));
            cmdData = bufferReader.read<decltype(cmdData)>();
            destroyShaderBuffer(cmdData);
        } break;
        case CmdType::destroyVertexAssemblyCmdType: {
            DestroyVertexAssemblyCmdData cmdData;
            assert(bufferReader.canRead(sizeof(cmdData)));
            cmdData = bufferReader.read<decltype(cmdData)>();
            destroyVertexAssembly(cmdData);
        } break;
        case CmdType::destroyTexture2DCmdType: {
            DestroyTexture2DCmdData cmdData;
            assert(bufferReader.canRead(sizeof(cmdData)));
            cmdData = bufferReader.read<decltype(cmdData)>();
            destroyTexture2D(cmdData);
        } break;
        case CmdType::destroyTexture2DArrayCmdType: {
            DestroyTexture2DArrayCmdData cmdData;
            assert(bufferReader.canRead(sizeof(cmdData)));
            cmdData = bufferReader.read<decltype(cmdData)>();
            destroyTexture2DArray(cmdData);
        } break;
        case CmdType::destroyVertexShaderCmdType: {
            DestroyVertexShaderCmdData cmdData;
            assert(bufferReader.canRead(sizeof(cmdData)));
            cmdData = bufferReader.read<decltype(cmdData)>();
            destroyVertexShader(cmdData);
        } break;
        case CmdType::destroyFragmentShaderCmdType: {
            DestroyFragmentShaderCmdData cmdData;
            assert(bufferReader.canRead(sizeof(cmdData)));
            cmdData = bufferReader.read<decltype(cmdData)>();
            destroyFragmentShader(cmdData);
        } break;
        case CmdType::destroyShaderProgramCmdType: {
            DestroyShaderProgramCmdData cmdData;
            assert(bufferReader.canRead(sizeof(cmdData)));
            cmdData = bufferReader.read<decltype(cmdData)>();
            destroyShaderProgram(cmdData);
        } break;
        case CmdType::destroyUniformCmdType: {
            DestroyUniformCmdData cmdData;
            assert(bufferReader.canRead(sizeof(cmdData)));
            cmdData = bufferReader.read<decltype(cmdData)>();
            destroyUniform(cmdData);
        } break;
        default: {
            assert(false);
        }
        }
    }
}
} // namespace rendell