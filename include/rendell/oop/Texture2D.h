#pragma once
#include <rendell/DataType.h>
#include <rendell/ResourceId.h>
#include <rendell/TextureFormat.h>
#include <rendell/oop/raii.h>

namespace rendell {
bool isValid(Texture2DId texture2DId);

namespace oop {
class Sampler2DUniform;

class Texture2D final {
public:
    Texture2D(uint32_t width, uint32_t height, TextureFormat textureFormat, const byte_t *pixels);
    ~Texture2D();

    void setSubData(uint32_t width, uint32_t height, const byte_t *pixels, uint32_t widthOffset = 0,
                    uint32_t heightOffset = 0);

    void use(const Sampler2DUniform &uniform, uint32_t stage);

    inline Texture2DId getId() const { return _id; }

    inline bool isValid() const { return rendell::isValid(_id); }

private:
    uint32_t _width;
    uint32_t _height;
    TextureFormat _textureFormat;
    Texture2DId _id;
};

RENDELL_USE_RAII_FACTORY(Texture2D)
} // namespace oop
} // namespace rendell