#include "OpenGLTextureFormat.h"

#include <array>
#include <cassert>

namespace rendell {
constexpr size_t kTextureFormatCount = static_cast<size_t>(TextureFormat::Count);

using Info = OpenGLTextureFormatInfo;
constexpr std::array<Info, kTextureFormatCount> kTable{
    // UNORM
    Info{TextureFormat::R8_UN, GL_R8, GL_RED, GL_UNSIGNED_BYTE},
    Info{TextureFormat::R16_UN, GL_R16, GL_RED, GL_UNSIGNED_SHORT},
    Info{TextureFormat::RG8_UN, GL_RG8, GL_RG, GL_UNSIGNED_BYTE},
    Info{TextureFormat::RG16_UN, GL_RG16, GL_RG, GL_UNSIGNED_SHORT},
    Info{TextureFormat::RGBA8_UN, GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE},
    Info{TextureFormat::BGRA8_UN, GL_RGBA8, GL_BGRA, GL_UNSIGNED_BYTE},

    // NORM (Signed)
    Info{TextureFormat::R8_SN, GL_R8_SNORM, GL_RED, GL_BYTE},
    Info{TextureFormat::R16_SN, GL_R16_SNORM, GL_RED, GL_SHORT},
    Info{TextureFormat::RG8_SN, GL_RG8_SNORM, GL_RG, GL_BYTE},
    Info{TextureFormat::RG16_SN, GL_RG16_SNORM, GL_RG, GL_SHORT},
    Info{TextureFormat::RGBA8_SN, GL_RGBA8_SNORM, GL_RGBA, GL_BYTE},

    // UINT (Unsigned Integer)
    Info{TextureFormat::R8_UI, GL_R8UI, GL_RED_INTEGER, GL_UNSIGNED_BYTE},
    Info{TextureFormat::R16_UI, GL_R16UI, GL_RED_INTEGER, GL_UNSIGNED_SHORT},
    Info{TextureFormat::R32_UI, GL_R32UI, GL_RED_INTEGER, GL_UNSIGNED_INT},
    Info{TextureFormat::RG8_UI, GL_RG8UI, GL_RG_INTEGER, GL_UNSIGNED_BYTE},
    Info{TextureFormat::RG16_UI, GL_RG16UI, GL_RG_INTEGER, GL_UNSIGNED_SHORT},
    Info{TextureFormat::RG32_UI, GL_RG32UI, GL_RG_INTEGER, GL_UNSIGNED_INT},
    Info{TextureFormat::RGBA8_UI, GL_RGBA8UI, GL_RGBA_INTEGER, GL_UNSIGNED_BYTE},
    Info{TextureFormat::RGBA16_UI, GL_RGBA16UI, GL_RGBA_INTEGER, GL_UNSIGNED_SHORT},
    Info{TextureFormat::RGBA32_UI, GL_RGBA32UI, GL_RGBA_INTEGER, GL_UNSIGNED_INT},

    // INT (Signed Integer)
    Info{TextureFormat::R8_SI, GL_R8I, GL_RED_INTEGER, GL_BYTE},
    Info{TextureFormat::R16_SI, GL_R16I, GL_RED_INTEGER, GL_SHORT},
    Info{TextureFormat::R32_SI, GL_R32I, GL_RED_INTEGER, GL_INT},
    Info{TextureFormat::RG8_SI, GL_RG8I, GL_RG_INTEGER, GL_BYTE},
    Info{TextureFormat::RG16_SI, GL_RG16I, GL_RG_INTEGER, GL_SHORT},
    Info{TextureFormat::RG32_SI, GL_RG32I, GL_RG_INTEGER, GL_INT},
    Info{TextureFormat::RGBA8_SI, GL_RGBA8I, GL_RGBA_INTEGER, GL_BYTE},
    Info{TextureFormat::RGBA16_SI, GL_RGBA16I, GL_RGBA_INTEGER, GL_SHORT},
    Info{TextureFormat::RGBA32_SI, GL_RGBA32I, GL_RGBA_INTEGER, GL_INT},

    // FLOAT
    Info{TextureFormat::R16_F, GL_R16F, GL_RED, GL_HALF_FLOAT},
    Info{TextureFormat::R32_F, GL_R32F, GL_RED, GL_FLOAT},
    Info{TextureFormat::RG16_F, GL_RG16F, GL_RG, GL_HALF_FLOAT},
    Info{TextureFormat::RG32_F, GL_RG32F, GL_RG, GL_FLOAT},
    Info{TextureFormat::RGBA16_F, GL_RGBA16F, GL_RGBA, GL_HALF_FLOAT},
    Info{TextureFormat::RGBA32_F, GL_RGBA32F, GL_RGBA, GL_FLOAT},

    // SRGB
    Info{TextureFormat::RGBA8_SRGB, GL_SRGB8_ALPHA8, GL_RGBA, GL_UNSIGNED_BYTE},
    Info{TextureFormat::BGRA8_SRGB, GL_SRGB8_ALPHA8, GL_BGRA, GL_UNSIGNED_BYTE},
};

constexpr bool validateTable() {
    for (size_t i = 0; i < kTable.size(); i++) {
        if (i != static_cast<size_t>(kTable[i].textureFormat)) {
            return false;
        }
    }
    return true;
}

static_assert(kTable.size() == kTextureFormatCount, "OpenGLTextureFormatInfo table is wrong!");
static_assert(validateTable(), "OpenGLTextureFormatInfo table is invalid");

const OpenGLTextureFormatInfo &getOpenGLTextureFormatInfo(TextureFormat format) {
    assert(format != TextureFormat::Count);
    return kTable[static_cast<size_t>(format)];
}

} // namespace rendell