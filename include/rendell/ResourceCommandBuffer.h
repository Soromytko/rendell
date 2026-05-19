#pragma once
#include "DataType.h"
#include "ResourceId.h"
#include "TextureFormat.h"
#include <rendell/ResourceIdGuard.h>
#include <rendell/VertexLayout.h>

#include <vector>

namespace rendell {
class ResourceIdAllocator;

class ResourceCommandBuffer final {
    friend struct RendellExtractor;

public:
    ResourceCommandBuffer(InstanceId instanceId, ResourceIdAllocator &allocator);
    ~ResourceCommandBuffer();

    ResourceCommandBuffer(const ResourceCommandBuffer &) = delete;
    ResourceCommandBuffer(ResourceCommandBuffer &&) = delete;
    ResourceCommandBuffer &operator=(const ResourceCommandBuffer &) = delete;
    ResourceCommandBuffer &operator=(ResourceCommandBuffer &&) = delete;

    IndexBufferId createIndexBuffer(const index_t *data, size_t size);
    IndexBufferId createIndexBuffer(const IndexContainer &data);
    DynamicIndexBufferId createDynamicIndexBuffer(size_t size);
    VertexBufferId createVertexBuffer(const vertex_t *data, size_t size);
    VertexBufferId createVertexBuffer(const VertexContainer &data);
    DynamicVertexBufferId createDynamicVertexBuffer(size_t size);
    UniformBufferId createUniformBuffer(const byte_t *data, size_t size);
    UniformBufferId createUniformBuffer(const ByteContainer &data);
    ShaderBufferId createShaderBuffer(const byte_t *data, size_t size);
    ShaderBufferId createShaderBuffer(const ByteContainer &data);
    ShaderBufferId createShaderBuffer(size_t size);
    VertexAssemblyId createVertexAssembly(IndexBufferId indexBufferId,
                                          const std::vector<VertexBufferId> &vertexBufferIds,
                                          const std::vector<VertexLayout> &vertexLayouts = {});
    Texture2DId createTexture2D(uint32_t width, uint32_t height, TextureFormat format,
                                const byte_t *pixels);
    Texture2DArrayId createTexture2DArray(uint32_t width, uint32_t height, uint32_t count,
                                          TextureFormat format);
    VertexShaderId createVertexShader(const std::string &src, ResultCallback callback = nullptr);
    FragmentShaderId createFragmentShader(const std::string &src,
                                          ResultCallback callback = nullptr);
    ShaderProgramId createShaderProgram(VertexShaderId vertexShaderId,
                                        FragmentShaderId fragmentShaderId,
                                        ResultCallback callback = nullptr);

    UniformId createUniform(const std::string &name, UniformType type);
    UniformInt1Id createUniformInt1(const std::string &name);
    UniformInt2Id createUniformInt2(const std::string &name);
    UniformInt3Id createUniformInt3(const std::string &name);
    UniformInt4Id createUniformInt4(const std::string &name);
    UniformFloat1Id createUniformFloat1(const std::string &name);
    UniformFloat2Id createUniformFloat2(const std::string &name);
    UniformFloat3Id createUniformFloat3(const std::string &name);
    UniformFloat4Id createUniformFloat4(const std::string &name);
    UniformMat4Id createUniformMat4(const std::string &name);
    UniformSampler2DId createUniformSampler2D(const std::string &name);

    void setSubData(DynamicIndexBufferId dynamicIndexBufferId, const index_t *data, size_t size,
                    size_t offset);
    void setSubData(DynamicVertexBufferId dynamicVertexBufferId, const vertex_t *data, size_t size,
                    size_t offset);
    void setSubData(ShaderBufferId shaderBufferId, const byte_t *data, size_t size, size_t offset);
    void setSubData(Texture2DId texture2DId, uint32_t width, uint32_t height,
                    TextureFormat textureFormat, const byte_t *pixels, uint32_t widthOffset = 0,
                    uint32_t heightOffset = 0);
    void setSubData(Texture2DArrayId texture2DArrayId, uint32_t index, uint32_t width,
                    uint32_t height, TextureFormat textureFormat, const byte_t *pixels,
                    uint32_t widthOffset = 0, uint32_t heightOffset = 0);

    void destroy(IndexBufferId indexBufferId);
    void destroy(VertexBufferId vertexBufferId);
    void destroy(UniformBufferId uniformBufferId);
    void destroy(ShaderBufferId shaderBufferId);
    void destroy(VertexAssemblyId vertexAssemblyId);
    void destroy(Texture2DId texture2DId);
    void destroy(Texture2DArrayId texture2DArrayId);
    void destroy(VertexShaderId vertexShaderId);
    void destroy(FragmentShaderId fragmentShaderId);
    void destroy(ShaderProgramId shaderProgramId);
    void destroy(UniformId uniformId);

    IndexBufferIdGuard createIndexBufferGuard(const index_t *data, size_t size);
    IndexBufferIdGuard createIndexBufferGuard(const IndexContainer &data);
    DynIndexBufferIdGuard createDynamicIndexBufferGuard(size_t size);
    VertexBufferIdGuard createVertexBufferGuard(const vertex_t *data, size_t size);
    VertexBufferIdGuard createVertexBufferGuard(const VertexContainer &data);
    DynVertexBufferIdGuard createDynamicVertexBufferGuard(size_t size);
    UniformBufferIdGuard createUniformBufferGuard(const byte_t *data, size_t size);
    UniformBufferIdGuard createUniformBufferGuard(const ByteContainer &data);
    ShaderBufferIdGuard createShaderBufferGuard(const byte_t *data, size_t size);
    ShaderBufferIdGuard createShaderBufferGuard(const ByteContainer &data);
    ShaderBufferIdGuard createShaderBufferGuard(size_t size);
    VertexAssemblyIdGuard createVertexAssemblyGuard(IndexBufferId indexBufferId,
                                          const std::vector<VertexBufferId> &vertexBufferIds,
                                          const std::vector<VertexLayout> &vertexLayouts = {});
    Texture2DIdGuard createTexture2DGuard(uint32_t width, uint32_t height, TextureFormat format,
                                const byte_t *pixels);
    Texture2DArrayIdGuard createTexture2DArrayGuard(uint32_t width, uint32_t height,
                                                      uint32_t count,
                                          TextureFormat format);
    VertexShaderIdGuard createVertexShaderGuard(const std::string &src,
                                                  ResultCallback callback = nullptr);
    FragmentShaderIdGuard createFragmentShaderGuard(const std::string &src,
                                          ResultCallback callback = nullptr);
    ShaderProgramIdGuard createShaderProgramGuard(VertexShaderId vertexShaderId,
                                        FragmentShaderId fragmentShaderId,
                                        ResultCallback callback = nullptr);

    void reset();

    bool isEmpty() const;

private:
    InstanceId _instanceId;
    ResourceIdAllocator &_allocator;

    static constexpr size_t _implSize = 584;
    static constexpr size_t _implAlign = 8;
    alignas(_implAlign) std::byte _implStorage[_implSize];
};
} // namespace rendell