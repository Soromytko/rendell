#include <rendell/oop/UniformBuffer.h>
#include <rendell/rendell.h>

namespace rendell {
namespace oop {
UniformBuffer::UniformBuffer(const byte_t *data, size_t size) {
    _id = rendell::createUniformBuffer(data, size);
}

UniformBuffer::UniformBuffer(const ByteContainer &data) {
    _id = rendell::createUniformBuffer(data);
}

UniformBuffer::~UniformBuffer() {
    rendell::destroy(_id);
}
} // namespace oop
} // namespace rendell
