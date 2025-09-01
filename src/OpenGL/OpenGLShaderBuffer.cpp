#include <OpenGL/OpenGLShaderBuffer.h>

#include "OpenGLUtils.h"

namespace rendell {
OpenGLShaderBuffer::OpenGLShaderBuffer(const byte_t *data, size_t size, bool isDynamic) {
    glGenBuffers(1, &_ssbo);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, _ssbo);
    glBufferData(GL_SHADER_STORAGE_BUFFER, size, static_cast<const void *>(data),
                 isDynamic ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
}

OpenGLShaderBuffer::~OpenGLShaderBuffer() {
    glDeleteBuffers(1, &_ssbo);
}

void OpenGLShaderBuffer::bind(uint32_t binding) const {
    _binding = binding;
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, _binding, _ssbo);
}

void OpenGLShaderBuffer::unbind() const {
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, _binding, 0);
}

void OpenGLShaderBuffer::setSubData(const byte_t *data, size_t size, size_t offset) {
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, _ssbo);
    glBufferSubData(GL_SHADER_STORAGE_BUFFER, static_cast<GLintptr>(offset),
                    static_cast<GLsizeiptr>(size), static_cast<const void *>(data));
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
}
} // namespace rendell