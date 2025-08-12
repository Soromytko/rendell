#pragma once
#include "IndexBuffer.h"
#include "VertexBuffer.h"
#include "private/defines.h"
#include <iostream>
#include <memory>

namespace rendell {
class VertexArray {
protected:
    VertexArray() = default;
    virtual ~VertexArray() = default;

public:
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

RENDELL_DECLARE_SHARED_PTR_FACTORY(VertexArray)
} // namespace rendell