#include "OpenGLFactory.h"
#include "OpenGLFragmentShader.h"
#include "OpenGLIndexBuffer.h"
#include "OpenGLShaderBuffer.h"
#include "OpenGLShaderProgram.h"
#include "OpenGLTexture2D.h"
#include "OpenGLTexture2DArray.h"
#include "OpenGLUniformBuffer.h"
#include "OpenGLVertexArray.h"
#include "OpenGLVertexBuffer.h"
#include "OpenGLVertexShader.h"

namespace rendell {
IndexBufferSharedPtr OpenGLFactory::createIndexBuffer(ArrayRef<uint32_t> data) {
    return makeOpenGLIndexBuffer(data);
}

VertexBufferSharedPtr OpenGLFactory::createVertexBuffer(ArrayRef<float> data) {
    return makeOpenGLVertexBuffer(data);
}

VertexArraySharedPtr
OpenGLFactory::createVertexArrayBuffer(const IndexBufferSharedPtr &indexBuffer,
                                       const std::vector<VertexBufferSharedPtr> &vertexBuffers) {
    return makeOpenGLVertexArray(indexBuffer, vertexBuffers);
}

UniformBufferSharedPtr OpenGLFactory::createUniformBuffer(ArrayRef<uint8_t> data) {
    return makeOpenGLUniformBuffer(data);
}

ShaderBufferSharedPtr OpenGLFactory::createShaderBuffer(ArrayRef<uint8_t> data) {
    return makeOpenGLShaderBuffer(data);
}

VertexShaderSharedPtr OpenGLFactory::createVertexShader(ArrayRef<char> data) {
    return makeOpenGLVertexShader(data);
}

FragmentShaderSharedPtr OpenGLFactory::createFragmentShader(ArrayRef<char> data) {
    return makeOpenGLFragmentShader(data);
}

ShaderProgramSharedPtr OpenGLFactory::createShaderProgram(VertexShaderSharedPtr vertexShader,
                                                          FragmentShaderSharedPtr fragmentShader) {
    return makeOpenGLShaderProgram(vertexShader, fragmentShader);
}

Texture2DSharedPtr OpenGLFactory::createTexture2D(uint32_t width, uint32_t height,
                                                  TextureFormat format, ArrayRef<uint8_t> pixels) {
    return makeOpenGLTexture2D(width, height, format, pixels);
}

Texture2DArraySharedPtr OpenGLFactory::createTexture2DArray(uint32_t width, uint32_t height,
                                                            uint32_t count, TextureFormat format,
                                                            ArrayRef<uint8_t> pixels) {
    return makeOpenGLTexture2DArray(width, height, count, format, pixels);
}
} // namespace rendell