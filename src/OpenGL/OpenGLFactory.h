#pragma once
#include <Backend/Factory.h>

namespace rendell {
class OpenGLFactory final : public Factory {
public:
    OpenGLFactory() = default;
    ~OpenGLFactory() = default;

    IndexBufferSharedPtr createIndexBuffer(ArrayRef<uint32_t> data) override;
    VertexBufferSharedPtr createVertexBuffer(ArrayRef<float> data) override;
    VertexArraySharedPtr
    createVertexArrayBuffer(const IndexBufferSharedPtr &indexBuffer,
                            const std::vector<VertexBufferSharedPtr> &vertexBuffers) override;
    UniformBufferSharedPtr createUniformBuffer(ArrayRef<uint8_t> data) override;
    ShaderBufferSharedPtr createShaderBuffer(ArrayRef<uint8_t> data) override;
    VertexShaderSharedPtr createVertexShader(ArrayRef<char> data) override;
    FragmentShaderSharedPtr createFragmentShader(ArrayRef<char> data) override;
    ShaderProgramSharedPtr createShaderProgram(VertexShaderSharedPtr vertexShader,
                                               FragmentShaderSharedPtr fragmentShader) override;
    Texture2DSharedPtr createTexture2D(uint32_t width, uint32_t height, TextureFormat format,
                                       ArrayRef<uint8_t> pixels) override;
    Texture2DArraySharedPtr createTexture2DArray(uint32_t width, uint32_t height, uint32_t count,
                                                 TextureFormat format,
                                                 ArrayRef<uint8_t> pixels) override;
};

} // namespace rendell
