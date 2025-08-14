#include <Factory.h>

namespace rendell {
class OpenGLFactory final : public Factory {
public:
    OpenGLFactory() = default;
    ~OpenGLFactory() = default;

    IndexBufferSharedPtr createIndexBuffer(std::vector<uint32_t> &&indices) const override;
    VertexBufferSharedPtr createVertexBuffer(std::vector<float> &&data) const override;
    VertexArraySharedPtr createVertexArray() const override;
    VertexArraySharedPtr
    createVertexArray(IndexBufferSharedPtr indexBuffer,
                      std::initializer_list<VertexBufferSharedPtr> buffers) const override;
    ShaderProgramSharedPtr createshaderProgram(std::string &&vertexSrc,
                                               std::string &&fragmentSrc) const override;
    Texture2DSharedPtr createTexture2D(uint32_t width, uint32_t height, TextureFormat format,
                                       const uint8_t *pixels) const override;
    Texture2DArraySharedPtr createTexture2DArray(uint32_t width, uint32_t height, uint32_t count,
                                                 TextureFormat format) const override;
    ShaderBufferSharedPtr createShaderBuffer(const void *data, size_t size) const override;
    UniformBufferSharedPtr createUniformBuffer(const void *data, size_t size) const override;
};

RENDELL_USE_RAII_FACTORY(OpenGLFactory)

} // namespace rendell