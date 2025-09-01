#include <rendell/oop/Texture2D.h>
#include <rendell/oop/Uniform.h>
#include <rendell/rendell.h>

#include <cassert>

namespace rendell {
namespace oop {
Texture2D::Texture2D(uint32_t width, uint32_t height, TextureFormat textureFormat,
                     const byte_t *pixels)
    : _width(width)
    , _height(height)
    , _textureFormat(textureFormat) {
    assert(width > 0);
    assert(height > 0);
    assert(pixels);
    _id = rendell::createTexture2D(width, height, textureFormat, pixels);
}

Texture2D::~Texture2D() {
    rendell::destroy(_id);
}

void Texture2D::setSubData(uint32_t width, uint32_t height, const byte_t *pixels,
                           uint32_t widthOffset, uint32_t heightOffset) {
    assert(width > 0);
    assert(height > 0);
    assert(pixels);
    rendell::setSubData(_id, width, height, _textureFormat, pixels, widthOffset, heightOffset);
}

void Texture2D::use(const Sampler2DUniform &uniform, uint32_t stage) {
    rendell::setTexture2D(uniform.getId(), _id, stage);
}
} // namespace oop
} // namespace rendell
