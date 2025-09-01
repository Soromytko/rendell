#include <OpenGL/OpenGLVertexBuffer.h>

#include <glad/glad.h>

namespace rendell {
OpenGLVertexBuffer::OpenGLVertexBuffer(const vertex_t *data, size_t size, bool isDynamic) {
    glCreateBuffers(1, &_bufferId);
    glBindBuffer(GL_ARRAY_BUFFER, _bufferId);
    glBufferData(GL_ARRAY_BUFFER, size * sizeof(vertex_t), static_cast<const void *>(data),
                 isDynamic ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);
}

OpenGLVertexBuffer::~OpenGLVertexBuffer() {
    glDeleteBuffers(1, &_bufferId);
}

void OpenGLVertexBuffer::bind() const {
    glBindBuffer(GL_ARRAY_BUFFER, _bufferId);
}

void OpenGLVertexBuffer::unbind() const {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

int OpenGLVertexBuffer::getStride() const {
    return _stride;
}

const std::vector<OpenGLVertexBufferLayout> &OpenGLVertexBuffer::getLayouts() const {
    return _layouts;
}

void OpenGLVertexBuffer::addLayout(const OpenGLVertexBufferLayout &layout) {
    _layouts.push_back(layout);
    calculateOffsetsAndStride();
}

void OpenGLVertexBuffer::setLayouts(const std::vector<OpenGLVertexBufferLayout> &layouts) {
    _layouts = layouts;
    calculateOffsetsAndStride();
}

void OpenGLVertexBuffer::setSubData(const vertex_t *data, size_t size, size_t offset) {
    glBindBuffer(GL_ARRAY_BUFFER, _bufferId);
    glBufferSubData(GL_ARRAY_BUFFER, static_cast<GLintptr>(offset),
                    static_cast<GLsizei>(size) * sizeof(vertex_t), static_cast<const void *>(data));
}

void OpenGLVertexBuffer::calculateOffsetsAndStride() {
    size_t offset = 0;
    _stride = 0;
    for (OpenGLVertexBufferLayout &layout : _layouts) {
        layout.setOffset(offset);
        offset += layout.getSize();
        _stride += static_cast<int>(layout.getSize());
    }
}
} // namespace rendell
