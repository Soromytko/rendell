#include <rendell/ShaderBuffer.h>

namespace rendell {
ShaderBuffer::ShaderBuffer(const void *data, size_t size)
    : _data(data)
    , _size(size) {
}

const void *ShaderBuffer::getData() const {
    return _data;
}

size_t ShaderBuffer::getSize() const {
    return _size;
}
} // namespace rendell