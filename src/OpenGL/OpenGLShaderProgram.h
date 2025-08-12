#pragma once
#include <glad/glad.h>
#include <rendell/ShaderProgram.h>

namespace rendell {
class OpenGLShaderProgram final : public ShaderProgram {
public:
    OpenGLShaderProgram(std::string &&vertexSrc, std::string &&fragmentSrc);
    ~OpenGLShaderProgram();
    void setVertexShaderSrc(std::string &&vertexSrc) override;
    void setFragmentShaderSrc(std::string &&fragmentSrc) override;
    bool compile(std::string *vertexInfoLog = nullptr,
                 std::string *fragmentInfoLog = nullptr) const override;
    bool link(std::string *infoLog = nullptr) const override;
    void freeSrc() override;
    void bind() const override;
    void unbind() const override;

    uint32_t getUniformIndex(const std::string &uniformName) const override;
    void setUniformInt1(uint32_t uniformIndex, int value) const override;
    void setUniformInt2(uint32_t uniformIndex, int v0, int v1) const override;
    void setUniformInt3(uint32_t uniformIndex, int v0, int v1, int v2) const override;
    void setUniformInt4(uint32_t uniformIndex, int v0, int v1, int v2, int v3) const override;
    void setUniformUint1(uint32_t uniformIndex, uint32_t value) const override;
    void setUniformFloat1(uint32_t uniformIndex, float value) const override;
    void setUniformFloat2(uint32_t uniformIndex, float v0, float v1) const override;
    void setUniformFloat3(uint32_t uniformIndex, float v0, float v1, float v2) const override;
    void setUniformFloat4(uint32_t uniformIndex, float v0, float v1, float v2,
                          float v3) const override;
    void setUniformVec2(uint32_t uniformIndex, const float *data) const override;
    void setUniformVec3(uint32_t uniformIndex, const float *data) const override;
    void setUniformVec4(uint32_t uniformIndex, const float *data) const override;
    void setUniformMat4(uint32_t uniformIndex, const float *data) const override;

    uint32_t getUniformBufferIndex(const std::string &uniformName) const override;
    void setUniformBufferBinding(const std::string &uniformName, uint32_t dataBinding) override;
    void setUniformBufferBinding(uint32_t uniformIndex, uint32_t dataBinding) override;
    uint32_t getShaderBufferIndex(const std::string &bufferName) const override;

    void setShaderBufferBinding(const std::string &bufferName, uint32_t binding) const override;
    void setShaderBufferBinding(uint32_t bufferIndex, uint32_t binding) const override;

private:
    GLuint _vertexShaderId{};
    GLuint _fragmentShaderId{};
    GLuint _shaderProgramId{};
};

RENDELL_DECLARE_SHARED_PTR_FACTORY(OpenGLShaderProgram)
} // namespace rendell
