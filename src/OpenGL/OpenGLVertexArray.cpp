#include "OpenGLVertexArray.h"

namespace rendell {
OpenGLVertexArray::OpenGLVertexArray()
    : VertexArray() {
    glCreateVertexArrays(1, &_vertexArrayId);
}

OpenGLVertexArray::OpenGLVertexArray(IndexBufferSharedPtr indexBuffer,
                                     std::initializer_list<VertexBufferSharedPtr> buffers)
    : VertexArray() {
    glCreateVertexArrays(1, &_vertexArrayId);

    setIndexBuffer(indexBuffer);
    for (auto it = buffers.begin(); it != buffers.end(); it++) {
        addVertexBuffer(*it);
    }
}

OpenGLVertexArray::~OpenGLVertexArray() {
    glCreateVertexArrays(1, &_vertexArrayId);
}

void OpenGLVertexArray::bind() const {
    glBindVertexArray(_vertexArrayId);
}

void OpenGLVertexArray::unbind() const {
    glBindVertexArray(0);
}

void OpenGLVertexArray::setIndexBuffer(IndexBufferSharedPtr indexBuffer) {
    VertexArray::setIndexBuffer(indexBuffer);

    if (!indexBuffer) {
        return;
    }

    bind();
    indexBuffer->bind();
}

static GLenum convertShaderTypeToOpenGLType(ShaderDataType type) {
    switch (type) {
    case ShaderDataType::int1:
    case ShaderDataType::int2:
    case ShaderDataType::int3:
        return GL_INT;
    case ShaderDataType::float1:
    case ShaderDataType::float2:
    case ShaderDataType::float3:
        return GL_FLOAT;
    }
    return 0;
}

void OpenGLVertexArray::addVertexBuffer(VertexBufferSharedPtr vertexBuffer) {
    VertexArray::addVertexBuffer(vertexBuffer);

    bind();
    vertexBuffer->bind();

    int index = 0;
    for (const VertexBufferLayout &layout : vertexBuffer->getLayouts()) {
        const GLint size = layout.getComponentCountByShaderType();
        const GLenum type = convertShaderTypeToOpenGLType(layout.getType());
        const GLboolean normalized = layout.getNormalized() ? GL_TRUE : GL_FALSE;
        const GLsizei stride = vertexBuffer->getStride();
        const void *offset = reinterpret_cast<const void *>(layout.getOffset());

        glEnableVertexAttribArray(index);

        switch (layout.getType()) {
        case ShaderDataType::int1:
        case ShaderDataType::int2:
        case ShaderDataType::int3:
        case ShaderDataType::int4: {
            glVertexAttribIPointer(index, size, type, stride, offset);
            break;
        }
        case ShaderDataType::float1:
        case ShaderDataType::float2:
        case ShaderDataType::float3:
        case ShaderDataType::float4:
            glVertexAttribPointer(index, size, type, normalized, stride, offset);
            break;
        }

        index++;
    }
}
} // namespace rendell
