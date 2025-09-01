#include <OpenGL/OpenGLTexture2D.h>

#include <logging.h>

#include "OpenGLUtils.h"

namespace rendell {
OpenGLTexture2D::OpenGLTexture2D(uint32_t width, uint32_t height, TextureFormat format,
                                 const byte_t *pixels)
    : _width(width)
    , _height(height)
    , _format(format) {
    glCreateTextures(GL_TEXTURE_2D, 1, &_textureId);

    glTextureStorage2D(_textureId, 1, convertTextureFormatToSizedFormat(format),
                       static_cast<GLsizei>(width), static_cast<GLsizei>(height));

    glTextureSubImage2D(_textureId, 0, 0, 0, static_cast<GLsizei>(width),
                        static_cast<GLsizei>(height), convertTextureFormatToBaseFormat(format),
                        GL_UNSIGNED_BYTE, static_cast<const void *>(pixels));

    glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

OpenGLTexture2D::~OpenGLTexture2D() {
    glDeleteTextures(1, &_textureId);
}

void OpenGLTexture2D::setSubData(uint32_t width, uint32_t height, const byte_t *pixels,
                                 uint32_t widthOffset, uint32_t heightOffset) {
    if (!pixels || _textureId == 0) {
        return;
    }

    if (width + widthOffset > _width) {
        RENDELL_WARNING("width + widthOffset ({}) exceeds texture width ({})", width + widthOffset,
                        _width);
        width = _width - widthOffset;
    }
    if (height + heightOffset > _height) {
        RENDELL_WARNING("height + heightOffset ({}) exceeds texture height ({})",
                        height + heightOffset, _height);
        height = _height - heightOffset;
    }

    glTextureSubImage2D(_textureId, 0, static_cast<GLint>(widthOffset),
                        static_cast<GLint>(heightOffset), static_cast<GLsizei>(width),
                        static_cast<GLsizei>(height), convertTextureFormatToBaseFormat(_format),
                        GL_UNSIGNED_BYTE, static_cast<const void *>(pixels));
}

void OpenGLTexture2D::bind(GLuint textureBlock) const {
    _textureBlock = textureBlock;
    glBindTextureUnit(_textureBlock, _textureId);
}

void OpenGLTexture2D::unbind() const {
    glBindTextureUnit(_textureBlock, 0);
}

} // namespace rendell