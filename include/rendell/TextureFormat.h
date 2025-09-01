#pragma once
#include <cstddef>

namespace rendell {
enum class TextureFormat {
    R,
    RG,
    RGB,
    BGR,
    RGBA,
    BGRA,
    R_INT,
    RG_INT,
    RGB_INT,
    BGR_INT,
    RGBA_INT,
    BGRA_INT,
};

size_t getTextureFormatSize(TextureFormat format);
} // namespace rendell