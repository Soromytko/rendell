#pragma once
#include <ResourceExecutor.h>

namespace rendell {
class OpenGLResourceExecutor final : public ResourceExecutor {
public:
    OpenGLResourceExecutor() = default;
    ~OpenGLResourceExecutor() = default;

    void createIndexBuffer(const CreateIndexBufferCmdData &cmd) override;
    void createVertexBuffer(const CreateVertexBufferCmdData &cmd) override;
    void createUniformBuffer(const CreateUniformBufferCmdData &cmd) override;
    void createShaderBuffer(const CreateShaderBufferCmdData &cmd) override;
    void createVertexAssembly(const CreateVertexAssemblyCmdData &cmd) override;
    void createTexture2D(const CreateTexture2DCmdData &cmd) override;
    void createTexture2DArray(const CreateTexture2DArrayCmdData &cmd) override;
    void createVertexShader(const CreateVertexShaderCmdData &cmd) override;
    void createFragmentShader(const CreateFragmentShaderCmdData &cmd) override;
    void createShaderProgram(const CreateShaderProgramCmdData &cmd) override;
    void createUniform(const CreateUniformCmdData &cmd) override;

    void setIndexBufferSubData(const SetIndexBufferSubDataCmdData &cmd) override;
    void setVertexBufferSubData(const SetVertexBufferSubDataCmdData &cmd) override;
    void setShaderBufferSubData(const SetShaderBufferSubDataCmdData &cmd) override;
    void setTexture2DSubData(const SetTexture2DSubDataCmdData &cmd) override;
    void setTexture2DArraySubData(const SetTexture2DArraySubDataCmdData &cmd) override;

    void destroyIndexBuffer(const DestroyIndexBufferCmdData &cmd) override;
    void destroyVertexBuffer(const DestroyVertexBufferCmdData &cmd) override;
    void destroyUniformBuffer(const DestroyUniformBufferCmdData &cmd) override;
    void destroyShaderBuffer(const DestroyShaderBufferCmdData &cmd) override;
    void destroyVertexAssembly(const DestroyVertexAssemblyCmdData &cmd) override;
    void destroyTexture2D(const DestroyTexture2DCmdData &cmd) override;
    void destroyTexture2DArray(const DestroyTexture2DArrayCmdData &cmd) override;
    void destroyVertexShader(const DestroyVertexShaderCmdData &cmd) override;
    void destroyFragmentShader(const DestroyFragmentShaderCmdData &cmd) override;
    void destroyShaderProgram(const DestroyShaderProgramCmdData &cmd) override;
    void destroyUniform(const DestroyUniformCmdData &cmdData) override;
};
} // namespace rendell