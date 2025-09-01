#include <OpenGL/OpenGLResourceExecutor.h>

#include <CallbackTable.h>
#include <OpenGL/OpenGLResourceStorage.h>
#include <rendell/hash.h>

#include <logging.h>

namespace rendell {
void OpenGLResourceExecutor::createIndexBuffer(const CreateIndexBufferCmdData &cmd) {
    OpenGLIndexBufferUniquePtr indexBuffer;
    if (cmd.dataKey) {
        IndexContainer dataContainer =
            _resourceDataProvider->indexBufferDataContainerStorage.retrieve(cmd.dataKey);
        indexBuffer = makeUniqueOpenGLIndexBuffer(dataContainer.getData(), dataContainer.getSize(),
                                                  cmd.isDynamic);
    } else {
        indexBuffer = makeUniqueOpenGLIndexBuffer(nullptr, cmd.dataSize, cmd.isDynamic);
    }
    getIndexBufferStorage().store(cmd.id.index, std::move(indexBuffer));
}

void OpenGLResourceExecutor::createVertexBuffer(const CreateVertexBufferCmdData &cmd) {
    OpenGLVertexBufferUniquePtr vertgexBuffer;
    if (cmd.dataKey) {
        VertexContainer dataContainer =
            _resourceDataProvider->vertexBufferDataContainerStorage.retrieve(cmd.dataKey);
        vertgexBuffer = makeUniqueOpenGLVertexBuffer(dataContainer.getData(),
                                                     dataContainer.getSize(), cmd.isDynamic);
    } else {
        vertgexBuffer = makeUniqueOpenGLVertexBuffer(nullptr, cmd.dataSize, cmd.isDynamic);
    }
    getVertexBufferStorage().store(cmd.id.index, std::move(vertgexBuffer));
}

void OpenGLResourceExecutor::createUniformBuffer(const CreateUniformBufferCmdData &cmd) {
}

void OpenGLResourceExecutor::createShaderBuffer(const CreateShaderBufferCmdData &cmd) {
    OpenGLShaderBufferUniquePtr shaderBuffer;
    if (cmd.dataKey) {
        ByteContainer dataContainer =
            _resourceDataProvider->byteContainerStorage.retrieve(cmd.dataKey);
        shaderBuffer =
            makeUniqueOpenGLShaderBuffer(dataContainer.getData(), dataContainer.getSize());
    } else {
        shaderBuffer = makeUniqueOpenGLShaderBuffer(nullptr, cmd.dataSize);
    }
    getShaderBufferStorage().store(cmd.id.index, std::move(shaderBuffer));
}

void OpenGLResourceExecutor::createVertexAssembly(const CreateVertexAssemblyCmdData &cmd) {
    OpenGLVertexArrayUniquePtr vertexArray = makeUniqueOpenGLVertexArray();

    // Set IndexBuffer
    {
        OpenGLIndexBuffer *indexBuffer =
            getIndexBufferStorage().find(cmd.indexBufferId.index).get();
        vertexArray->setIndexBuffer(indexBuffer);
    }

    // Set VertexBuffer
    {
        DataContainer<VertexBufferId> vertexBufferIds =
            _resourceDataProvider->vertexBufferIdsContainerStorage.retrieve(cmd.vertexBufferIdsKey);
        DataContainer<VertexLayout> vertexLayouts =
            _resourceDataProvider->vertexLayoutsContainerStorage.retrieve(cmd.vertexLayoutsKey);
        for (size_t i = 0, j = 0; i < vertexBufferIds.getSize(); i++) {
            const VertexBufferId vertexBufferId = vertexBufferIds.getData()[i];
            OpenGLVertexBuffer *vertexBuffer =
                getVertexBufferStorage().find(vertexBufferId.index).get();
            if (j < vertexLayouts.getSize()) {
                const VertexLayout &vertexLayout = vertexLayouts.getData()[j];
                const std::vector<VertexLayout::Attribute> &attributes =
                    vertexLayout.getAttributes();
                for (const VertexLayout::Attribute &attribute : attributes) {
                    vertexBuffer->addLayout(OpenGLVertexBufferLayout(
                        attribute.type, attribute.normalized, attribute.offset));
                }
                j++;
            }
            vertexArray->addVertexBuffer(vertexBuffer);
        }
    }
    getVertexArrayBufferStorage().store(cmd.id.index, std::move(vertexArray));
}

void OpenGLResourceExecutor::createTexture2D(const CreateTexture2DCmdData &cmd) {
    ByteContainer dataContainer = _resourceDataProvider->byteContainerStorage.retrieve(cmd.dataKey);
    OpenGLTexture2DUniquePtr texture2D =
        makeUniqueOpenGLTexture2D(cmd.width, cmd.height, cmd.format, dataContainer.getData());
    getTexture2DStorage().store(cmd.id.index, std::move(texture2D));
}

void OpenGLResourceExecutor::createTexture2DArray(const CreateTexture2DArrayCmdData &cmd) {
    OpenGLTexture2DArrayUniquePtr texture2DArray =
        makeUniqueOpenGLTexture2DArray(cmd.width, cmd.height, cmd.count, cmd.format);
    getTexture2DArrayStorage().store(cmd.id.index, std::move(texture2DArray));
}

void OpenGLResourceExecutor::createVertexShader(const CreateVertexShaderCmdData &cmd) {
    StringContainer srcContainer =
        _resourceDataProvider->stringContainerStorage.retrieve(cmd.srcKey);
    const char *src = srcContainer.getData();
    assert(src);
    OpenGLVertexShaderUniquePtr vertexShader = makeUniqueOpenGLVertexShader(src);
    std::string infoLog;
    const bool success = vertexShader->compile(&infoLog);
    if (auto maybeCallback = getResultCallbackTable().tyrRetrive(hash(cmd.id)); maybeCallback) {
        maybeCallback.value()(success, infoLog);
    }
    if (success) {
        getVertexShaderStorage().store(cmd.id.index, std::move(vertexShader));
    }
}

void OpenGLResourceExecutor::createFragmentShader(const CreateFragmentShaderCmdData &cmd) {
    StringContainer srcContainer =
        _resourceDataProvider->stringContainerStorage.retrieve(cmd.srcKey);
    const char *src = srcContainer.getData();
    assert(src);
    OpenGLFragmentShaderUniquePtr fragmentShader = makeUniqueOpenGLFragmentShader(src);
    std::string infoLog;
    const bool success = fragmentShader->compile(&infoLog);
    if (auto maybeCallback = getResultCallbackTable().tyrRetrive(hash(cmd.id)); maybeCallback) {
        maybeCallback.value()(success, infoLog);
    }
    if (success) {
        getFragmentShaderStorage().store(cmd.id.index, std::move(fragmentShader));
    }
}

void OpenGLResourceExecutor::createShaderProgram(const CreateShaderProgramCmdData &cmd) {
    const size_t vertexShaderIndex = cmd.vertexShaderId.index;
    const size_t fragmentShaderIndex = cmd.fragmentShaderId.index;

    OpenGLVertexShader *vertexShader = getVertexShaderStorage().find(vertexShaderIndex).get();
    OpenGLFragmentShader *fragmentShader =
        getFragmentShaderStorage().find(fragmentShaderIndex).get();
    OpenGLShaderProgramUniquePtr shaderProgram = makeUniqueOpenGLShaderProgram();
    std::string infoLog;
    const bool success =
        shaderProgram->link(vertexShader->getId(), fragmentShader->getId(), &infoLog);
    if (auto maybeCallback = getResultCallbackTable().tyrRetrive(hash(cmd.id)); maybeCallback) {
        maybeCallback.value()(success, infoLog);
    }
    if (success) {
        getShaderProgramStorage().store(cmd.id.index, std::move(shaderProgram));
    }
}

void OpenGLResourceExecutor::createUniform(const CreateUniformCmdData &cmd) {
    StringContainer nameContainer =
        _resourceDataProvider->stringContainerStorage.retrieve(cmd.nameKey);
    std::string name(nameContainer.getData(), nameContainer.getSize());
    storeUniformName(hash(cmd.id), std::move(name));
}

void OpenGLResourceExecutor::setIndexBufferSubData(const SetIndexBufferSubDataCmdData &cmd) {
    OpenGLIndexBuffer *indexBuffer = getIndexBufferStorage().find(cmd.id.index).get();
    assert(indexBuffer);
    IndexContainer dataContainer =
        _resourceDataProvider->indexBufferDataContainerStorage.retrieve(cmd.dataKey);
    indexBuffer->setSubData(dataContainer.getData(), dataContainer.getSize(), cmd.offset);
}

void OpenGLResourceExecutor::setVertexBufferSubData(const SetVertexBufferSubDataCmdData &cmd) {
    OpenGLVertexBuffer *vertexBuffer = getVertexBufferStorage().find(cmd.id.index).get();
    assert(vertexBuffer);
    VertexContainer dataContainer =
        _resourceDataProvider->vertexBufferDataContainerStorage.retrieve(cmd.dataKey);
    vertexBuffer->setSubData(dataContainer.getData(), dataContainer.getSize(), cmd.offset);
}

void OpenGLResourceExecutor::setShaderBufferSubData(const SetShaderBufferSubDataCmdData &cmd) {
    OpenGLShaderBuffer *shaderBuffer = getShaderBufferStorage().find(cmd.id.index).get();
    assert(shaderBuffer);
    ByteContainer dataContainer = _resourceDataProvider->byteContainerStorage.retrieve(cmd.dataKey);
    shaderBuffer->setSubData(dataContainer.getData(), dataContainer.getSize(), cmd.offset);
}

void OpenGLResourceExecutor::setTexture2DSubData(const SetTexture2DSubDataCmdData &cmd) {
    OpenGLTexture2D *texture2D = getTexture2DStorage().find(cmd.id.index).get();
    assert(texture2D);
    ByteContainer dataContainer = _resourceDataProvider->byteContainerStorage.retrieve(cmd.dataKey);
    texture2D->setSubData(cmd.width, cmd.height, dataContainer.getData(), cmd.widthOffset,
                          cmd.heightOffset);
}

void OpenGLResourceExecutor::setTexture2DArraySubData(const SetTexture2DArraySubDataCmdData &cmd) {
    OpenGLTexture2DArray *texture2DArray = getTexture2DArrayStorage().find(cmd.id.index).get();
    assert(texture2DArray);
    ByteContainer dataContainer = _resourceDataProvider->byteContainerStorage.retrieve(cmd.dataKey);
    texture2DArray->setSubTextureData(cmd.index, cmd.width, cmd.height, dataContainer.getData());
}

void OpenGLResourceExecutor::destroyIndexBuffer(const DestroyIndexBufferCmdData &cmd) {
    getIndexBufferStorage().destroy(cmd.id.index);
}

void OpenGLResourceExecutor::destroyVertexBuffer(const DestroyVertexBufferCmdData &cmd) {
    getVertexBufferStorage().destroy(cmd.id.index);
}

void OpenGLResourceExecutor::destroyUniformBuffer(const DestroyUniformBufferCmdData &cmd) {
    getUniformBufferStorage().destroy(cmd.id.index);
}

void OpenGLResourceExecutor::destroyShaderBuffer(const DestroyShaderBufferCmdData &cmd) {
    getShaderBufferStorage().destroy(cmd.id.index);
}

void OpenGLResourceExecutor::destroyVertexAssembly(const DestroyVertexAssemblyCmdData &cmd) {
    getVertexArrayBufferStorage().destroy(cmd.id.index);
}

void OpenGLResourceExecutor::destroyTexture2D(const DestroyTexture2DCmdData &cmd) {
    getTexture2DStorage().destroy(cmd.id.index);
}

void OpenGLResourceExecutor::destroyTexture2DArray(const DestroyTexture2DArrayCmdData &cmd) {
    getTexture2DArrayStorage().destroy(cmd.id.index);
}

void OpenGLResourceExecutor::destroyVertexShader(const DestroyVertexShaderCmdData &cmd) {
    getVertexShaderStorage().destroy(cmd.id.index);
}

void OpenGLResourceExecutor::destroyFragmentShader(const DestroyFragmentShaderCmdData &cmd) {
    getFragmentShaderStorage().destroy(cmd.id.index);
}

void OpenGLResourceExecutor::destroyShaderProgram(const DestroyShaderProgramCmdData &cmd) {
    getShaderProgramStorage().destroy(cmd.id.index);
}

void OpenGLResourceExecutor::destroyUniform(const DestroyUniformCmdData &cmd) {
    const size_t key = hash(cmd.id);
    removeUniformName(key);
}
} // namespace rendell