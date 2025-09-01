#pragma once
#pragma once
#include "Command.h"
#include "ResourceDataProvider.h"
#include <Buffers/ByteBuffer.h>

namespace rendell {
class ResourceExecutor {
public:
    ResourceExecutor() = default;
    virtual ~ResourceExecutor() = default;

    void execute(const ByteBuffer &resourceBuffer,
                 ResourceDataProviderSharedPtr resourceDataProvider);

    virtual void createIndexBuffer(const CreateIndexBufferCmdData &cmd) = 0;
    virtual void createVertexBuffer(const CreateVertexBufferCmdData &cmd) = 0;
    virtual void createUniformBuffer(const CreateUniformBufferCmdData &cmd) = 0;
    virtual void createShaderBuffer(const CreateShaderBufferCmdData &cmd) = 0;
    virtual void createVertexAssembly(const CreateVertexAssemblyCmdData &cmd) = 0;
    virtual void createTexture2D(const CreateTexture2DCmdData &cmd) = 0;
    virtual void createTexture2DArray(const CreateTexture2DArrayCmdData &cmd) = 0;
    virtual void createVertexShader(const CreateVertexShaderCmdData &cmd) = 0;
    virtual void createFragmentShader(const CreateFragmentShaderCmdData &cmd) = 0;
    virtual void createShaderProgram(const CreateShaderProgramCmdData &cmd) = 0;
    virtual void createUniform(const CreateUniformCmdData &cmd) = 0;

    virtual void setIndexBufferSubData(const SetIndexBufferSubDataCmdData &cmd) = 0;
    virtual void setVertexBufferSubData(const SetVertexBufferSubDataCmdData &cmd) = 0;
    virtual void setShaderBufferSubData(const SetShaderBufferSubDataCmdData &cmd) = 0;
    virtual void setTexture2DSubData(const SetTexture2DSubDataCmdData &cmd) = 0;
    virtual void setTexture2DArraySubData(const SetTexture2DArraySubDataCmdData &cmd) = 0;

    virtual void destroyIndexBuffer(const DestroyIndexBufferCmdData &cmd) = 0;
    virtual void destroyVertexBuffer(const DestroyVertexBufferCmdData &cmd) = 0;
    virtual void destroyUniformBuffer(const DestroyUniformBufferCmdData &cmd) = 0;
    virtual void destroyShaderBuffer(const DestroyShaderBufferCmdData &cmd) = 0;
    virtual void destroyVertexAssembly(const DestroyVertexAssemblyCmdData &cmd) = 0;
    virtual void destroyTexture2D(const DestroyTexture2DCmdData &cmd) = 0;
    virtual void destroyTexture2DArray(const DestroyTexture2DArrayCmdData &cmd) = 0;
    virtual void destroyVertexShader(const DestroyVertexShaderCmdData &cmd) = 0;
    virtual void destroyFragmentShader(const DestroyFragmentShaderCmdData &cmd) = 0;
    virtual void destroyShaderProgram(const DestroyShaderProgramCmdData &cmd) = 0;
    virtual void destroyUniform(const DestroyUniformCmdData &cmd) = 0;

protected:
    ResourceDataProviderSharedPtr _resourceDataProvider;
};
} // namespace rendell