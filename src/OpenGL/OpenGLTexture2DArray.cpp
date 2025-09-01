#include <OpenGL/OpenGLTexture2DArray.h>

#include "OpenGLUtils.h"

namespace rendell {
OpenGLTexture2DArray::OpenGLTexture2DArray(uint32_t width, uint32_t height, uint32_t count,
                                           TextureFormat format)
    : _format(format) {
    glCreateTextures(GL_TEXTURE_2D_ARRAY, 1, &_id);

    glTextureStorage3D(_id, 1, convertTextureFormatToSizedFormat(_format),
                       static_cast<GLsizei>(width), static_cast<GLsizei>(height),
                       static_cast<GLsizei>(count));

    glTextureParameteri(_id, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTextureParameteri(_id, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTextureParameteri(_id, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTextureParameteri(_id, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
}

OpenGLTexture2DArray::~OpenGLTexture2DArray() {
    glDeleteTextures(1, &_id);
}

void OpenGLTexture2DArray::setSubTextureData(uint32_t index, uint32_t width, uint32_t height,
                                             const byte_t *pixels) {
    glTextureSubImage3D(_id, 0, 0, 0, static_cast<GLint>(index), static_cast<GLint>(width),
                        static_cast<GLint>(height), 1, convertTextureFormatToBaseFormat(_format),
                        GL_UNSIGNED_BYTE, static_cast<const void *>(pixels));
}

void OpenGLTexture2DArray::bind(GLuint textureBlock) const {
    _textureBlock = textureBlock;
    glBindTextureUnit(_textureBlock, _id);
}

void OpenGLTexture2DArray::unbind() const {
    glBindTextureUnit(_textureBlock, 0);
}

} // namespace rendell
