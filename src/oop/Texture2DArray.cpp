#include <rendell/oop/Texture2DArray.h>
#include <rendell/rendell.h>

#include <cassert>

namespace rendell {
namespace oop {
Texture2DArray::Texture2DArray(uint32_t width, uint32_t height, uint32_t count,
                               TextureFormat textureFormat)
    : _width(width)
    , _height(height)
    , _count(count)
    , _textureFormat(textureFormat) {
    assert(width > 0);
    assert(height > 0);
    assert(count > 0);
    _id = createTexture2DArray(width, height, count, textureFormat);
}

Texture2DArray::~Texture2DArray() {
    destroy(_id);
}

void Texture2DArray::setSubData(uint32_t index, uint32_t width, uint32_t height,
                                const byte_t *pixels, uint32_t widthOffset, uint32_t heightOffset) {
    assert(width > 0);
    assert(height > 0);
    assert(index < _count);
    assert(pixels);
    rendell::setSubData(_id, index, width, height, _textureFormat, pixels, widthOffset,
                        heightOffset);
}

} // namespace oop
} // namespace rendell
