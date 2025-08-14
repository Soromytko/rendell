#pragma once
#include "IndexBuffer.h"
#include "ShaderBuffer.h"
#include "ShaderProgram.h"
#include "Texture2D.h"
#include "Texture2DArray.h"
#include "UniformBuffer.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include <vector>

namespace rendell {
IndexBufferSharedPtr createIndexBuffer(std::vector<uint32_t> indices);
IndexBufferSharedPtr createIndexBuffer(const uint32_t *data, size_t size);

VertexBufferSharedPtr createVertexBuffer(std::vector<float> data);
VertexBufferSharedPtr createVertexBuffer(const float *data, size_t size);

VertexArraySharedPtr createVertexArray();
VertexArraySharedPtr createVertexArray(IndexBufferSharedPtr indexBuffer,
                                       std::initializer_list<VertexBufferSharedPtr> buffers);

UniformBufferSharedPtr createUniformBuffer(const void *data, size_t size);

ShaderBufferSharedPtr createShaderBuffer(const void *data, size_t size);

ShaderProgramSharedPtr createShaderProgram(std::string vertexSrc, std::string fragmentSrc);

Texture2DSharedPtr createTexture2D(uint32_t width, uint32_t height, TextureFormat format,
                                   const uint8_t *pixels);
Texture2DArraySharedPtr createTexture2DArray(uint32_t width, uint32_t height, uint32_t count,
                                             TextureFormat format);
} // namespace rendell
