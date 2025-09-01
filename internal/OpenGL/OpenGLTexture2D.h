#pragma once
#include <glad/glad.h>
#include <rendell/DataType.h>
#include <rendell/TextureFormat.h>
#include <rendell/oop/raii.h>

namespace rendell {
class OpenGLTexture2D final {
public:
    OpenGLTexture2D(uint32_t width, uint32_t height, TextureFormat format, const byte_t *pixels);
    ~OpenGLTexture2D();

    void setSubData(uint32_t width, uint32_t height, const byte_t *pixels, uint32_t widthOffset = 0,
                    uint32_t heightOffset = 0);
    void bind(GLuint textureBlock = 0) const;
    void unbind() const;

private:
    uint32_t _width;
    uint32_t _height;
    TextureFormat _format;
    GLuint _textureId{};
    mutable uint32_t _textureBlock{0};
};

RENDELL_USE_RAII_FACTORY(OpenGLTexture2D)
} // namespace rendell