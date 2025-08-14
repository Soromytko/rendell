#pragma once
#include "IndexBuffer.h"
#include "VertexBuffer.h"
#include "private/defines.h"
#include <iostream>
#include <memory>

namespace rendell {
class VertexArray {
public:
    VertexArray() = default;
    virtual ~VertexArray() = default;

    virtual void bind() const = 0;
    virtual void unbind() const = 0;
    virtual void setIndexBuffer(IndexBufferSharedPtr indexBuffer);
    virtual void addVertexBuffer(VertexBufferSharedPtr vertexBuffer);
    const std::vector<VertexBufferSharedPtr> &getVertexBuffers() const;
    const IndexBufferSharedPtr &getIndexBuffer() const;

protected:
    std::vector<VertexBufferSharedPtr> _vertexBuffers{};
    IndexBufferSharedPtr _indexBuffer{};
};

RENDELL_USE_RAII(VertexArray)
} // namespace rendell