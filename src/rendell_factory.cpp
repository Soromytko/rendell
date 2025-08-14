#include <Factory.h>
#include <rendell/rendell_static.h>
#include <rendell_factory.h>

namespace rendell {
IndexBufferSharedPtr createIndexBuffer(std::vector<uint32_t> indices) {
    return getCurrentFactory()->createIndexBuffer(std::move(indices));
}

IndexBufferSharedPtr createIndexBuffer(const uint32_t *data, size_t size) {
    std::vector<uint32_t> vectorData(data, data + size);
    return getCurrentFactory()->createIndexBuffer(std::move(vectorData));
}

VertexBufferSharedPtr createVertexBuffer(std::vector<float> data) {
    return getCurrentFactory()->createVertexBuffer(std::move(data));
}

VertexBufferSharedPtr createVertexBuffer(const float *data, size_t size) {
    std::vector<float> vectorData(data, data + size);
    return getCurrentFactory()->createVertexBuffer(std::move(vectorData));
}

VertexArraySharedPtr createVertexArray() {
    return getCurrentFactory()->createVertexArray();
}

VertexArraySharedPtr createVertexArray(IndexBufferSharedPtr indexBuffer,
                                       std::initializer_list<VertexBufferSharedPtr> buffers) {
    return getCurrentFactory()->createVertexArray(indexBuffer, buffers);
}

UniformBufferSharedPtr createUniformBuffer(const void *data, size_t size) {
    return getCurrentFactory()->createUniformBuffer(data, size);
}

ShaderBufferSharedPtr createShaderBuffer(const void *data, size_t size) {
    return getCurrentFactory()->createShaderBuffer(data, size);
}

ShaderProgramSharedPtr createShaderProgram(std::string vertexSrc, std::string fragmentSrc) {
    return getCurrentFactory()->createshaderProgram(std::move(vertexSrc), std::move(fragmentSrc));
}

Texture2DSharedPtr createTexture2D(uint32_t width, uint32_t height, TextureFormat format,
                                   const uint8_t *pixels) {
    return getCurrentFactory()->createTexture2D(width, height, format, pixels);
}

Texture2DArraySharedPtr createTexture2DArray(uint32_t width, uint32_t height, uint32_t count,
                                             TextureFormat format) {
    return getCurrentFactory()->createTexture2DArray(width, height, count, format);
}
} // namespace rendell