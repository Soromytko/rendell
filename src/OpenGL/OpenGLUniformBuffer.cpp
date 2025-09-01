#include <OpenGL/OpenGLUniformBuffer.h>

namespace rendell {
OpenGLUniformBuffer::OpenGLUniformBuffer(const byte_t *data, size_t size) {
    glCreateBuffers(1, &_id);
    glNamedBufferData(_id, size, reinterpret_cast<const void *>(size), GL_DYNAMIC_DRAW);
}

void OpenGLUniformBuffer::bind(uint32_t binding) const {
    _binding = binding;
    glBindBufferBase(GL_UNIFORM_BUFFER, _binding, _id);
}

void OpenGLUniformBuffer::unbind() const {
    glBindBufferBase(GL_UNIFORM_BUFFER, _binding, 0);
}

void OpenGLUniformBuffer::setSubData(const byte_t *data, size_t size, size_t offset) const {
    glNamedBufferSubData(_id, offset, size, reinterpret_cast<const void *>(data));
}
} // namespace rendell