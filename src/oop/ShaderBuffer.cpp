#include <rendell/oop/ShaderBuffer.h>
#include <rendell/rendell.h>

#include <cassert>

namespace rendell {
namespace oop {
ShaderBuffer::ShaderBuffer(const byte_t *data, size_t size)
    : _size(size) {
    assert(data);
    assert(size > 0);
    _id = rendell::createShaderBuffer(data, size);
}

ShaderBuffer::ShaderBuffer(const ByteContainer &data)
    : _size(data.getSize()) {
    _id = rendell::createShaderBuffer(data);
}

ShaderBuffer::~ShaderBuffer() {
    rendell::destroy(_id);
}

void ShaderBuffer::setSubData(const byte_t *data, size_t size, size_t offset) {
    assert(data);
    assert(size > 0);
    assert(size <= _size);
    assert(offset < _size);
    rendell::setSubData(_id, data, size, offset);
}
} // namespace oop
} // namespace rendell
