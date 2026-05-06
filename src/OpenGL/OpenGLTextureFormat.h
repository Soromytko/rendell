#pragma once
#include <glad/glad.h>
#include <rendell/TextureFormat.h>

namespace rendell {
struct OpenGLTextureFormatInfo {
    TextureFormat textureFormat;
    GLenum internalFormat;
    GLenum format;
    GLenum type;
};

const OpenGLTextureFormatInfo &getOpenGLTextureFormatInfo(TextureFormat format);
} // namespace rendell