#include <rendell/oop/VertexBuffer.h>
#include <rendell/rendell.h>

#include <cassert>

namespace rendell {
namespace oop {
VertexBuffer::VertexBuffer(const vertex_t *data, size_t size) {
    assert(data);
    assert(size > 0);
    _id = createVertexBuffer(data, size);
}

VertexBuffer::VertexBuffer(const VertexContainer &data) {
    _id = createVertexBuffer(data);
}

VertexBuffer::~VertexBuffer() {
    destroy(_id);
}
} // namespace oop
} // namespace rendell
