#include "OpenGLTexture2D.h"

namespace rendell {
OpenGLTexture2D::OpenGLTexture2D(uint32_t width, uint32_t height, TextureFormat format,
                                 const uint8_t *pixels)
    : Texture2D(width, height, format, pixels) {
    glCreateTextures(GL_TEXTURE_2D, 1, &_textureId);

    glTextureStorage2D(_textureId, 1, convertTextureFormatToSizedFormat(_format),
                       static_cast<GLsizei>(_width), static_cast<GLsizei>(_height));

    glTextureSubImage2D(_textureId, 0, 0, 0, static_cast<GLsizei>(_width),
                        static_cast<GLsizei>(_height), convertTextureFormatToBaseFormat(_format),
                        GL_UNSIGNED_BYTE, static_cast<const void *>(_pixels));

    glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

OpenGLTexture2D::~OpenGLTexture2D() {
    glDeleteTextures(1, &_textureId);
}

void OpenGLTexture2D::bind(uint32_t textureBlock) const {
    _textureBlock = textureBlock;
    glBindTextureUnit(_textureBlock, _textureId);
}

void OpenGLTexture2D::unbind() const {
    glBindTextureUnit(_textureBlock, 0);
}

} // namespace rendell