#pragma once
#include <glad/glad.h>
#include <rendell/DataType.h>
#include <rendell/oop/raii.h>

namespace rendell {
class OpenGLUniformBuffer final {
public:
    OpenGLUniformBuffer(const byte_t *data, size_t size);
    ~OpenGLUniformBuffer() = default;

    void bind(uint32_t binding = 0) const;
    void unbind() const;
    void setSubData(const byte_t *data, size_t size, size_t offset = 0) const;

private:
    mutable uint32_t _binding{0};
    GLuint _id;
};

RENDELL_USE_RAII_FACTORY(OpenGLUniformBuffer)
} // namespace rendell