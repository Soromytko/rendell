#pragma once
#include <cstdint>
#include <raii.h>
#include <rendell/Ref.h>
#include <rendell/TextureFormat.h>

#include "IndexBuffer.h"
#include "ShaderBuffer.h"
#include "Texture2D.h"
#include "Texture2DArray.h"
#include "UniformBuffer.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

#include "FragmentShader.h"
#include "ShaderProgram.h"
#include "VertexShader.h"

namespace rendell {
class Factory {
public:
    Factory() = default;
    virtual ~Factory() = default;

    virtual IndexBufferSharedPtr createIndexBuffer(ArrayRef<uint32_t> data) = 0;
    virtual VertexBufferSharedPtr createVertexBuffer(ArrayRef<float> data) = 0;
    virtual VertexArraySharedPtr
    createVertexArrayBuffer(const IndexBufferSharedPtr &indexBuffer,
                            const std::vector<VertexBufferSharedPtr> &vertexBuffers) = 0;
    virtual UniformBufferSharedPtr createUniformBuffer(ArrayRef<uint8_t> data) = 0;
    virtual ShaderBufferSharedPtr createShaderBuffer(ArrayRef<uint8_t> data) = 0;
    virtual VertexShaderSharedPtr createVertexShader(ArrayRef<char> data) = 0;
    virtual FragmentShaderSharedPtr createFragmentShader(ArrayRef<char> data) = 0;
    virtual ShaderProgramSharedPtr createShaderProgram(VertexShaderSharedPtr vertexShader,
                                                       FragmentShaderSharedPtr fragmentShader) = 0;
    virtual Texture2DSharedPtr createTexture2D(uint32_t width, uint32_t height,
                                               TextureFormat format, ArrayRef<uint8_t> pixels) = 0;
    virtual Texture2DArraySharedPtr createTexture2DArray(uint32_t width, uint32_t height,
                                                         uint32_t count, TextureFormat format,
                                                         ArrayRef<uint8_t> pixels) = 0;
};
RENDELL_USE_RAII(Factory)
} // namespace rendell

namespace rendell {
Factory *getFactory();
void initOpenGLFactory();
void initVulkanFactory();
void initDirectX12Factory();
void releaseFactory();
} // namespace rendell