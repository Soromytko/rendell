#pragma once
#include "TextureFormat.h"
#include "private/defines.h"
#include <iostream>
#include <memory>
#include <vector>

namespace rendell {
class Texture2D {
public:
    Texture2D(uint32_t width, uint32_t height, TextureFormat format, const uint8_t *pixels);
    virtual ~Texture2D() = default;

    virtual void bind(uint32_t textureBlock = 0) const = 0;
    virtual void unbind() const = 0;

    uint32_t getWidth() const;
    uint32_t getHeight() const;
    TextureFormat getFormat() const;
    const uint8_t *getPixels() const;

protected:
    uint32_t _width;
    uint32_t _height;
    TextureFormat _format;
    const uint8_t *_pixels;
};

RENDELL_USE_RAII(Texture2D)
} // namespace rendell