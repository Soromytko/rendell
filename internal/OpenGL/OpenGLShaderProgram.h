#pragma once
#include <glad/glad.h>
#include <rendell/oop/raii.h>

#include <cstdint>
#include <string>
#include <unordered_map>

namespace rendell {
class OpenGLShaderProgram final {
public:
    OpenGLShaderProgram();
    ~OpenGLShaderProgram();

    bool link(GLuint vertexShader, GLuint fragmentShader, std::string *infoLog = nullptr) const;

    void bind() const;
    void unbind() const;

    GLint getUniformIndex(const char *uniformName) const;
    GLint getUniformIndex(const std::string &uniformName) const;

    void setUniformInt1(uint32_t uniformIndex, int value) const;
    void setUniformInt2(uint32_t uniformIndex, int v0, int v1) const;
    void setUniformInt3(uint32_t uniformIndex, int v0, int v1, int v2) const;
    void setUniformInt4(uint32_t uniformIndex, int v0, int v1, int v2, int v3) const;
    void setUniformUint1(uint32_t uniformIndex, uint32_t value) const;
    void setUniformFloat1(uint32_t uniformIndex, float value) const;
    void setUniformFloat2(uint32_t uniformIndex, float v0, float v1) const;
    void setUniformFloat3(uint32_t uniformIndex, float v0, float v1, float v2) const;
    void setUniformFloat4(uint32_t uniformIndex, float v0, float v1, float v2, float v3) const;
    void setUniformVec2(uint32_t uniformIndex, const float *data) const;
    void setUniformVec3(uint32_t uniformIndex, const float *data) const;
    void setUniformVec4(uint32_t uniformIndex, const float *data) const;
    void setUniformMat4(uint32_t uniformIndex, const float *data) const;

    uint32_t getUniformBufferIndex(const std::string &uniformName) const;
    void setUniformBufferBinding(const std::string &uniformName, uint32_t dataBinding);
    void setUniformBufferBinding(uint32_t uniformIndex, uint32_t dataBinding);
    uint32_t getShaderBufferIndex(const std::string &bufferName) const;

    void setShaderBufferBinding(const std::string &bufferName, uint32_t binding) const;
    void setShaderBufferBinding(uint32_t bufferIndex, uint32_t binding) const;

private:
    bool _linkStatus{false};
    std::string _linkInfoLog{};

    GLuint _shaderProgramId{};

    struct TransparentHash {
        using is_transparent = void;

        size_t operator()(std::string_view sv) const noexcept {
            return std::hash<std::string_view>{}(sv);
        }
    };

    struct TransparentEqual {
        using is_transparent = void;

        bool operator()(std::string_view a, std::string_view b) const noexcept { return a == b; }
    };

    mutable std::unordered_map<std::string, GLint, TransparentHash, TransparentEqual>
        _uniformIndexCache;
};

RENDELL_USE_RAII_FACTORY(OpenGLShaderProgram)
} // namespace rendell
