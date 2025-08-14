#pragma once
#include <rendell/IndexBuffer.h>
#include <rendell/ShaderBuffer.h>
#include <rendell/ShaderProgram.h>
#include <rendell/Texture2D.h>
#include <rendell/Texture2DArray.h>
#include <rendell/TextureFormat.h>
#include <rendell/UniformBuffer.h>
#include <rendell/VertexArray.h>
#include <rendell/VertexBuffer.h>
#include <vector>

namespace rendell {
class Factory {
public:
    Factory() = default;
    virtual ~Factory() = default;

    virtual IndexBufferSharedPtr createIndexBuffer(std::vector<uint32_t> &&indices) const = 0;
    virtual VertexBufferSharedPtr createVertexBuffer(std::vector<float> &&data) const = 0;
    virtual VertexArraySharedPtr createVertexArray() const = 0;
    virtual VertexArraySharedPtr
    createVertexArray(IndexBufferSharedPtr indexBuffer,
                      std::initializer_list<VertexBufferSharedPtr> buffers) const = 0;
    virtual ShaderProgramSharedPtr createshaderProgram(std::string &&vertexSrc,
                                                       std::string &&fragmentSrc) const = 0;
    virtual Texture2DSharedPtr createTexture2D(uint32_t width, uint32_t height,
                                               TextureFormat format,
                                               const uint8_t *pixels) const = 0;
    virtual Texture2DArraySharedPtr createTexture2DArray(uint32_t width, uint32_t height,
                                                         uint32_t count,
                                                         TextureFormat format) const = 0;
    virtual ShaderBufferSharedPtr createShaderBuffer(const void *data, size_t size) const = 0;
    virtual UniformBufferSharedPtr createUniformBuffer(const void *data, size_t size) const = 0;
};

RENDELL_USE_RAII(Factory)
} // namespace rendell