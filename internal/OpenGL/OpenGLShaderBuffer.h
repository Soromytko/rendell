#pragma once
#include <glad/glad.h>
#include <rendell/DataType.h>
#include <rendell/oop/raii.h>

namespace rendell {
class OpenGLShaderBuffer final {
public:
    OpenGLShaderBuffer(const byte_t *data, size_t size, bool isDynamic = true);
    ~OpenGLShaderBuffer();

    void bind(uint32_t binding = 0) const;
    void unbind() const;

    void setSubData(const byte_t *data, size_t size, size_t offset = 0);

private:
    GLuint _ssbo;
    mutable uint32_t _binding{0};
};

RENDELL_USE_RAII_FACTORY(OpenGLShaderBuffer)
} // namespace rendell