#include <rendell/TextureFormat.h>

#include <array>
#include <cassert>

namespace rendell {
constexpr size_t kTextureFormatCount = static_cast<size_t>(TextureFormat::Count);

using Info = TextureFormatInfo;
constexpr std::array<Info, kTextureFormatCount> kTextureFormatInfoTable{
    // UNORM
    Info{TextureFormat::R8_UN, "R8_UN", 1, 1, 1},
    Info{TextureFormat::R16_UN, "R16_UN", 2, 1, 1},
    Info{TextureFormat::RG8_UN, "RG8_UN", 2, 1, 1},
    Info{TextureFormat::RG16_UN, "RG16_UN", 4, 1, 1},
    Info{TextureFormat::RGBA8_UN, "RGBA8_UN", 4, 1, 1},
    Info{TextureFormat::BGRA8_UN, "BGRA8_UN", 4, 1, 1},

    // NORM
    Info{TextureFormat::R8_SN, "R8_SN", 1, 1, 1},
    Info{TextureFormat::R16_SN, "R16_SN", 2, 1, 1},
    Info{TextureFormat::RG8_SN, "RG8_SN", 2, 1, 1},
    Info{TextureFormat::RG16_SN, "RG16_SN", 4, 1, 1},
    Info{TextureFormat::RGBA8_SN, "RGBA8_SN", 4, 1, 1},

    // UINT
    Info{TextureFormat::R8_UI, "R8_UI", 1, 1, 1},
    Info{TextureFormat::R16_UI, "R16_UI", 2, 1, 1},
    Info{TextureFormat::R32_UI, "R32_UI", 4, 1, 1},
    Info{TextureFormat::RG8_UI, "RG8_UI", 2, 1, 1},
    Info{TextureFormat::RG16_UI, "RG16_UI", 4, 1, 1},
    Info{TextureFormat::RG32_UI, "RG32_UI", 8, 1, 1},
    Info{TextureFormat::RGBA8_UI, "RGBA8_UI", 4, 1, 1},
    Info{TextureFormat::RGBA16_UI, "RGBA16_UI", 8, 1, 1},
    Info{TextureFormat::RGBA32_UI, "RGBA32_UI", 16, 1, 1},

    // INT
    Info{TextureFormat::R8_SI, "R8_SI", 1, 1, 1},
    Info{TextureFormat::R16_SI, "R16_SI", 2, 1, 1},
    Info{TextureFormat::R32_SI, "R32_SI", 4, 1, 1},
    Info{TextureFormat::RG8_SI, "RG8_SI", 2, 1, 1},
    Info{TextureFormat::RG16_SI, "RG16_SI", 4, 1, 1},
    Info{TextureFormat::RG32_SI, "RG32_SI", 8, 1, 1},
    Info{TextureFormat::RGBA8_SI, "RGBA8_SI", 4, 1, 1},
    Info{TextureFormat::RGBA16_SI, "RGBA16_SI", 8, 1, 1},
    Info{TextureFormat::RGBA32_SI, "RGBA32_SI", 16, 1, 1},

    // FLOAT
    Info{TextureFormat::R16_F, "R16_F", 2, 1, 1},
    Info{TextureFormat::R32_F, "R32_F", 4, 1, 1},
    Info{TextureFormat::RG16_F, "RG16_F", 4, 1, 1},
    Info{TextureFormat::RG32_F, "RG32_F", 8, 1, 1},
    Info{TextureFormat::RGBA16_F, "RGBA16_F", 8, 1, 1},
    Info{TextureFormat::RGBA32_F, "RGBA32_F", 16, 1, 1},

    // SRGB
    Info{TextureFormat::RGBA8_SRGB, "RGBA8_SRGB", 4, 1, 1},
    Info{TextureFormat::BGRA8_SRGB, "BGRA8_SRGB", 4, 1, 1},
};

template <size_t Index> struct TableErrorAtIndex {
    static_assert(Index == -1, "Mismatched or missing format found at this index!");
};

template <size_t I = 0> constexpr bool validateTable() {
    if constexpr (I < kTextureFormatInfoTable.size()) {
        if constexpr (static_cast<size_t>(kTextureFormatInfoTable[I].format) != I) {
            [[maybe_unused]] TableErrorAtIndex<I> error;
            return false;
        } else {
            return validateTable<I + 1>();
        }
    }
    return true;
}

static_assert(kTextureFormatInfoTable.size() == kTextureFormatCount,
              "TextureFormatInfo table is wrong!");
static_assert(validateTable(), "TextureFormatInfo table is invalid!");

const TextureFormatInfo &getTextureFormatInfo(TextureFormat textureFormat) {
    assert(textureFormat != TextureFormat::Count);
    return kTextureFormatInfoTable[static_cast<size_t>(textureFormat)];
}
} // namespace rendell