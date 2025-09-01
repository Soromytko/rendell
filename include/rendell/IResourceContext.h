#pragma once
#include "DataType.h"
#include "ResourceId.h"
#include "TextureFormat.h"
#include <rendell/VertexLayout.h>

#include <vector>

namespace rendell {
class IResourceContext {
public:
    IResourceContext() = default;
    virtual ~IResourceContext() = default;

    virtual IndexBufferId createIndexBuffer(const index_t *data, size_t size) = 0;
    virtual IndexBufferId createIndexBuffer(const IndexContainer &data) = 0;
    virtual DynamicIndexBufferId createDynamicIndexBuffer(size_t size) = 0;
    virtual VertexBufferId createVertexBuffer(const vertex_t *data, size_t size) = 0;
    virtual VertexBufferId createVertexBuffer(const VertexContainer &data) = 0;
    virtual DynamicVertexBufferId createDynamicVertexBuffer(size_t size) = 0;
    virtual UniformBufferId createUniformBuffer(const byte_t *data, size_t size) = 0;
    virtual UniformBufferId createUniformBuffer(const ByteContainer &data) = 0;
    virtual ShaderBufferId createShaderBuffer(const byte_t *data, size_t size) = 0;
    virtual ShaderBufferId createShaderBuffer(const ByteContainer &data) = 0;
    virtual ShaderBufferId createShaderBuffer(size_t size) = 0;
    virtual VertexAssemblyId
    createVertexAssembly(IndexBufferId indexBufferId,
                         const std::vector<VertexBufferId> &vertexBufferIds,
                         const std::vector<VertexLayout> &vertexLayouts = {}) = 0;
    virtual Texture2DId createTexture2D(uint32_t width, uint32_t height, TextureFormat format,
                                        const byte_t *pixels) = 0;
    virtual Texture2DArrayId createTexture2DArray(uint32_t width, uint32_t height, uint32_t count,
                                                  TextureFormat format) = 0;
    virtual VertexShaderId createVertexShader(const std::string &src,
                                              ResultCallback callback = nullptr) = 0;
    virtual FragmentShaderId createFragmentShader(const std::string &src,
                                                  ResultCallback callback = nullptr) = 0;
    virtual ShaderProgramId createShaderProgram(VertexShaderId vertexShaderId,
                                                FragmentShaderId fragmentShaderId,
                                                ResultCallback callback = nullptr) = 0;

    virtual UniformId createUniform(const std::string &name, UniformType type) = 0;
    virtual UniformInt1Id createUniformInt1(const std::string &name) = 0;
    virtual UniformInt2Id createUniformInt2(const std::string &name) = 0;
    virtual UniformInt3Id createUniformInt3(const std::string &name) = 0;
    virtual UniformInt4Id createUniformInt4(const std::string &name) = 0;
    virtual UniformFloat1Id createUniformFloat1(const std::string &name) = 0;
    virtual UniformFloat2Id createUniformFloat2(const std::string &name) = 0;
    virtual UniformFloat3Id createUniformFloat3(const std::string &name) = 0;
    virtual UniformFloat4Id createUniformFloat4(const std::string &name) = 0;
    virtual UniformMat4Id createUniformMat4(const std::string &name) = 0;
    virtual UniformSampler2DId createUniformSampler2D(const std::string &name) = 0;

    virtual void setSubData(DynamicIndexBufferId dynamicIndexBufferId, const index_t *data,
                            size_t size, size_t offset) = 0;
    virtual void setSubData(DynamicVertexBufferId dynamicVertexBufferId, const vertex_t *data,
                            size_t size, size_t offset) = 0;
    virtual void setSubData(ShaderBufferId shaderBufferId, const byte_t *data, size_t size,
                            size_t offset) = 0;
    virtual void setSubData(Texture2DId texture2DId, uint32_t width, uint32_t height,
                            TextureFormat textureFormat, const byte_t *pixels,
                            uint32_t widthOffset = 0, uint32_t heightOffset = 0) = 0;
    virtual void setSubData(Texture2DArrayId texture2DArrayId, uint32_t index, uint32_t width,
                            uint32_t height, TextureFormat textureFormat, const byte_t *pixels,
                            uint32_t widthOffset = 0, uint32_t heightOffset = 0) = 0;

    virtual void destroy(IndexBufferId indexBufferId) = 0;
    virtual void destroy(VertexBufferId vertexBufferId) = 0;
    virtual void destroy(UniformBufferId uniformBufferId) = 0;
    virtual void destroy(ShaderBufferId shaderBufferId) = 0;
    virtual void destroy(VertexAssemblyId vertexAssemblyId) = 0;
    virtual void destroy(Texture2DId texture2DId) = 0;
    virtual void destroy(Texture2DArrayId texture2DArrayId) = 0;
    virtual void destroy(VertexShaderId vertexShaderId) = 0;
    virtual void destroy(FragmentShaderId fragmentShaderId) = 0;
    virtual void destroy(ShaderProgramId shaderProgramId) = 0;
    virtual void destroy(UniformId uniformId) = 0;
};
} // namespace rendell