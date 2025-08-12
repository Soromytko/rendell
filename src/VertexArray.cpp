#include "OpenGL/OpenGLVertexArray.h"
#include <rendell/VertexArray.h>

namespace rendell {
void VertexArray::setIndexBuffer(IndexBufferSharedPtr indexBuffer) {
    _indexBuffer = indexBuffer;
}

void VertexArray::addVertexBuffer(VertexBufferSharedPtr vertexBuffer) {
    _vertexBuffers.push_back(vertexBuffer);
}

const std::vector<VertexBufferSharedPtr> &VertexArray::getVertexBuffers() const {
    return _vertexBuffers;
}

const IndexBufferSharedPtr &VertexArray::getIndexBuffer() const {
    return _indexBuffer;
}
} // namespace rendell
