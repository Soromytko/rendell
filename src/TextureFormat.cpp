#include <rendell/TextureFormat.h>

#include <cassert>

namespace rendell {
size_t getTextureFormatSize(TextureFormat format) {
    switch (format) {
    case TextureFormat::R:
        return 1;
    case TextureFormat::RG:
        return 2;
    case TextureFormat::RGB:
        [[fallthrough]];
    case TextureFormat::BGR:
        return 3;
    case TextureFormat::RGBA:
    case TextureFormat::BGRA:
        return 4;
    case TextureFormat::R_INT:
        return 4;
    case TextureFormat::RG_INT:
        return 8;
    case TextureFormat::RGB_INT:
        [[fallthrough]];
    case TextureFormat::BGR_INT:
        return 12;
    case TextureFormat::RGBA_INT:
        [[fallthrough]];
    case TextureFormat::BGRA_INT:
        return 16;
    }

    assert(false && "Unhandled TextureFormat");
    return 0;
}
} // namespace rendell