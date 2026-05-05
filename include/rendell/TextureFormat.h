#pragma once
#include <cstdint>

namespace rendell {
enum class TextureFormat {
    // Unsigned normalized
    R8_UN,
    R16_UN,
    RG8_UN,
    RG16_UN,
    RGBA8_UN,
    BGRA8_UN,

    // Signed normalized
    R8_SN,
    R16_SN,
    RG8_SN,
    RG16_SN,
    RGBA8_SN,

    // Unsigned integer
    R8_UI,
    R16_UI,
    R32_UI,
    RG8_UI,
    RG16_UI,
    RG32_UI,
    RGBA8_UI,
    RGBA16_UI,
    RGBA32_UI,

    // Signed integer
    R8_SI,
    R16_SI,
    R32_SI,
    RG8_SI,
    RG16_SI,
    RG32_SI,
    RGBA8_SI,
    RGBA16_SI,
    RGBA32_SI,

    // Floating point
    R16_F,
    R32_F,
    RG16_F,
    RG32_F,
    RGBA16_F,
    RGBA32_F,

    // SRGB
    RGBA8_SRGB,
    BGRA8_SRGB,

    Count,
};

struct TextureFormatInfo {
    TextureFormat format;
    const char *name;
    uint16_t blockSize;
    uint8_t blockWidth;
    uint8_t blockHeight;
};

const TextureFormatInfo &getTextureFormatInfo(TextureFormat textureFormat);
} // namespace rendell