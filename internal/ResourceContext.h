#pragma once
#include <rendell/IResourceContext.h>

#include "DataContainerStorage.h"
#include "ResourceCommandBuffer.h"
#include "ResourceDataProvider.h"

namespace rendell {
class ResourceContext final : public IResourceContext {
public:
    ResourceContext();
    ~ResourceContext() = default;

    IndexBufferId createIndexBuffer(const index_t *data, size_t size) override;
    IndexBufferId createIndexBuffer(const IndexContainer &data) override;
    DynamicIndexBufferId createDynamicIndexBuffer(size_t size) override;
    VertexBufferId createVertexBuffer(const vertex_t *data, size_t size) override;
    VertexBufferId createVertexBuffer(const VertexContainer &data) override;
    DynamicVertexBufferId createDynamicVertexBuffer(size_t size) override;
    UniformBufferId createUniformBuffer(const byte_t *data, size_t size) override;
    UniformBufferId createUniformBuffer(const ByteContainer &data) override;
    ShaderBufferId createShaderBuffer(const byte_t *data, size_t size) override;
    ShaderBufferId createShaderBuffer(const ByteContainer &data) override;
    ShaderBufferId createShaderBuffer(size_t size) override;
    VertexAssemblyId createVertexAssembly(IndexBufferId indexBufferId,
                                          const std::vector<VertexBufferId> &vertexBufferIds,
                                          const std::vector<VertexLayout> &vertexLayouts) override;
    Texture2DId createTexture2D(uint32_t width, uint32_t height, TextureFormat format,
                                const byte_t *pixels) override;
    Texture2DArrayId createTexture2DArray(uint32_t width, uint32_t height, uint32_t count,
                                          TextureFormat format) override;
    VertexShaderId createVertexShader(const std::string &src,
                                      ResultCallback callback = nullptr) override;
    FragmentShaderId createFragmentShader(const std::string &src,
                                          ResultCallback callback = nullptr) override;
    ShaderProgramId createShaderProgram(VertexShaderId vertexShaderId,
                                        FragmentShaderId fragmentShaderId,
                                        ResultCallback callback = nullptr) override;

    UniformId createUniform(const std::string &name, UniformType type) override;
    UniformInt1Id createUniformInt1(const std::string &name) override;
    UniformInt2Id createUniformInt2(const std::string &name) override;
    UniformInt3Id createUniformInt3(const std::string &name) override;
    UniformInt4Id createUniformInt4(const std::string &name) override;
    UniformFloat1Id createUniformFloat1(const std::string &name) override;
    UniformFloat2Id createUniformFloat2(const std::string &name) override;
    UniformFloat3Id createUniformFloat3(const std::string &name) override;
    UniformFloat4Id createUniformFloat4(const std::string &name) override;
    UniformMat4Id createUniformMat4(const std::string &name) override;
    UniformSampler2DId createUniformSampler2D(const std::string &name) override;

    void setSubData(DynamicIndexBufferId dynamicIndexBufferId, const index_t *data, size_t size,
                    size_t offset) override;
    void setSubData(DynamicVertexBufferId dynamicVertexBufferId, const vertex_t *data, size_t size,
                    size_t offset) override;
    void setSubData(ShaderBufferId shaderBufferId, const byte_t *data, size_t size,
                    size_t offset) override;
    void setSubData(Texture2DId texture2DId, uint32_t width, uint32_t height,
                    TextureFormat textureFormat, const byte_t *pixels, uint32_t widthOffset = 0,
                    uint32_t heightOffset = 0) override;
    void setSubData(Texture2DArrayId texture2DArrayId, uint32_t index, uint32_t width,
                    uint32_t height, TextureFormat textureFormat, const byte_t *pixels,
                    uint32_t widthOffset = 0, uint32_t heightOffset = 0) override;

    void destroy(IndexBufferId indexBufferId) override;
    void destroy(VertexBufferId vertexBufferId) override;
    void destroy(UniformBufferId uniformBufferId) override;
    void destroy(ShaderBufferId shaderBufferId) override;
    void destroy(VertexAssemblyId vertexAssemblyId) override;
    void destroy(Texture2DId texture2DId) override;
    void destroy(Texture2DArrayId texture2DArrayId) override;
    void destroy(VertexShaderId vertexShaderId) override;
    void destroy(FragmentShaderId fragmentShaderId) override;
    void destroy(ShaderProgramId shaderProgramId) override;
    void destroy(UniformId uniformId) override;

    const ByteBuffer &getCommandBuffer() const;
    ResourceDataProviderSharedPtr getResourceDataProvider() const;

    void reset();

private:
    ByteBuffer _resourceCommandBuffer{config::resourceByteBufferReservedSize};
    ResourceDataProviderSharedPtr _resourceDataProvider;
};

RENDELL_USE_RAII_FACTORY(ResourceContext)
} // namespace rendell