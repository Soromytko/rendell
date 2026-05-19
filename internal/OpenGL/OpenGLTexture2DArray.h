#pragma once
#include <glad/glad.h>
#include <rendell/DataType.h>
#include <rendell/TextureFormat.h>

namespace rendell {
class OpenGLTexture2DArray final {
public:
    OpenGLTexture2DArray(uint32_t width, uint32_t height, uint32_t count, TextureFormat format);
    ~OpenGLTexture2DArray();

    void setSubTextureData(uint32_t index, uint32_t width, uint32_t height, const byte_t *pixels);
    void bind(GLuint textureBlock = 0) const;
    void unbind() const;

private:
    GLuint _id;
    TextureFormat _format;
    mutable GLuint _textureBlock{0};
};

} // namespace rendell