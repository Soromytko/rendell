#pragma once
#include "OpenGLVertexBufferLayout.h"
#include <glad/glad.h>
#include <rendell/DataType.h>
#include <rendell/oop/raii.h>

namespace rendell {
class OpenGLVertexBuffer final {
public:
    OpenGLVertexBuffer(const vertex_t *data, size_t size, bool isDynamic = false);
    ~OpenGLVertexBuffer();

    void bind() const;
    void unbind() const;

    int getStride() const;
    const std::vector<OpenGLVertexBufferLayout> &getLayouts() const;
    void addLayout(const OpenGLVertexBufferLayout &layout);
    void setLayouts(const std::vector<OpenGLVertexBufferLayout> &layouts);

    void setSubData(const vertex_t *data, size_t size, size_t offset = 0);

private:
    void calculateOffsetsAndStride();

    GLuint _bufferId{};
    int _stride = 0;
    std::vector<OpenGLVertexBufferLayout> _layouts{};
};

RENDELL_USE_RAII_FACTORY(OpenGLVertexBuffer)
} // namespace rendell