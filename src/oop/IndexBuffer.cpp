#include <rendell/oop/IndexBuffer.h>
#include <rendell/rendell.h>

#include <cassert>

namespace rendell {
namespace oop {
IndexBuffer::IndexBuffer(const index_t *data, size_t size) {
    assert(data);
    assert(size > 0);
    _id = createIndexBuffer(data, size);
}

IndexBuffer::IndexBuffer(const IndexContainer &data) {
    _id = createIndexBuffer(data);
}

IndexBuffer::~IndexBuffer() {
    destroy(_id);
}
} // namespace oop
} // namespace rendell
