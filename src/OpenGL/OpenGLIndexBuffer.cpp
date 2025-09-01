#include <OpenGL/OpenGLIndexBuffer.h>

namespace rendell {
OpenGLIndexBuffer::OpenGLIndexBuffer(const index_t *data, size_t size, bool isDynamic) {
    if (!glCreateBuffers) {
        assert(false);
    }
    glCreateBuffers(1, &_bufferId);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _bufferId);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, static_cast<GLsizei>(size) * sizeof(index_t),
                 static_cast<const void *>(data), isDynamic ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);
    _count = size;
}

OpenGLIndexBuffer::~OpenGLIndexBuffer() {
    glDeleteBuffers(1, &_bufferId);
}

void OpenGLIndexBuffer::bind() const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _bufferId);
}

void OpenGLIndexBuffer::unbind() const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void OpenGLIndexBuffer::setSubData(const index_t *data, size_t size, size_t offset) {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _bufferId);
    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, static_cast<GLintptr>(offset),
                    static_cast<GLsizei>(size) * sizeof(index_t), static_cast<const void *>(data));
}
} // namespace rendell
