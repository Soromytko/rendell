#pragma once
#include "OpenGLIndexBuffer.h"
#include <glad/glad.h>
#include <rendell/oop/raii.h>

namespace rendell {
class OpenGLIndexBuffer;
class OpenGLVertexBuffer;
} // namespace rendell

namespace rendell {
class OpenGLVertexArray final {
public:
    OpenGLVertexArray();
    ~OpenGLVertexArray();

    inline size_t getIndexCount() const { return _indexCount; }

    void bind() const;
    void unbind() const;

    void setIndexBuffer(const OpenGLIndexBuffer *indexBuffer);
    void addVertexBuffer(const OpenGLVertexBuffer *vertexBuffer);

private:
    size_t _indexCount{};
    GLuint _vertexArrayId{};
};

RENDELL_USE_RAII_FACTORY(OpenGLVertexArray)

} // namespace rendell