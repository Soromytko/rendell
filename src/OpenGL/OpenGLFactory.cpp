#include "OpenGLFactory.h"
#include "OpenGLIndexBuffer.h"
#include "OpenGLShaderBuffer.h"
#include "OpenGLShaderProgram.h"
#include "OpenGLTexture2D.h"
#include "OpenGLTexture2DArray.h"
#include "OpenGLUniformBuffer.h"
#include "OpenGLVertexArray.h"
#include "OpenGLVertexBuffer.h"
#include <glad/glad.h>

namespace rendell {
IndexBufferSharedPtr OpenGLFactory::createIndexBuffer(std::vector<uint32_t> &&indices) const {
    return makeOpenGLIndexBuffer(std::move(indices));
}

VertexBufferSharedPtr OpenGLFactory::createVertexBuffer(std::vector<float> &&data) const {
    return makeOpenGLVertexBuffer(std::move(data));
}

VertexArraySharedPtr OpenGLFactory::createVertexArray() const {
    return makeOpenGLVertexArray();
}

VertexArraySharedPtr
OpenGLFactory::createVertexArray(IndexBufferSharedPtr indexBuffer,
                                 std::initializer_list<VertexBufferSharedPtr> buffers) const {
    return makeOpenGLVertexArray(indexBuffer, buffers);
}

ShaderProgramSharedPtr OpenGLFactory::createshaderProgram(std::string &&vertexSrc,
                                                          std::string &&fragmentSrc) const {
    return makeOpenGLShaderProgram(std::move(vertexSrc), std::move(fragmentSrc));
}

Texture2DSharedPtr OpenGLFactory::createTexture2D(uint32_t width, uint32_t height,
                                                  TextureFormat format,
                                                  const uint8_t *pixels) const {
    return makeOpenGLTexture2D(width, height, format, pixels);
}

Texture2DArraySharedPtr OpenGLFactory::createTexture2DArray(uint32_t width, uint32_t height,
                                                            uint32_t count,
                                                            TextureFormat format) const {
    return makeOpenGLTexture2DArray(width, height, count, format);
}

ShaderBufferSharedPtr OpenGLFactory::createShaderBuffer(const void *data, size_t size) const {
    return makeOpenGLShaderBuffer(data, size);
}

UniformBufferSharedPtr OpenGLFactory::createUniformBuffer(const void *data, size_t size) const {
    return makeOpenGLUniformBuffer(data, size);
}

} // namespace rendell