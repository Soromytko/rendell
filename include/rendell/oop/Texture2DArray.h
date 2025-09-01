#pragma once
#include <rendell/DataType.h>
#include <rendell/ResourceId.h>
#include <rendell/TextureFormat.h>
#include <rendell/oop/raii.h>

namespace rendell {
bool isValid(Texture2DArrayId texture2DArrayId);
void setTexture2D(UniformSampler2DId uniformSamplerId, Texture2DArrayId textureId, uint32_t stage);

namespace oop {
class Texture2DArray final {
public:
    Texture2DArray(uint32_t width, uint32_t height, uint32_t count, TextureFormat textureFormat);
    ~Texture2DArray();

    void setSubData(uint32_t index, uint32_t width, uint32_t height, const byte_t *pixels,
                    uint32_t widthOffset = 0, uint32_t heightOffset = 0);

    inline void use(UniformSampler2DId uniformSamplerId, uint32_t stage) {
        rendell::setTexture2D(uniformSamplerId, _id, stage);
    }

    inline Texture2DArrayId getId() const { return _id; }

    inline bool isValid() const { return rendell::isValid(_id); }

private:
    uint32_t _width;
    uint32_t _height;
    uint32_t _count;
    TextureFormat _textureFormat;
    Texture2DArrayId _id;
};

RENDELL_USE_RAII_FACTORY(Texture2DArray)
} // namespace oop
} // namespace rendell