#pragma once
#include "Color.h"
#include "DataType.h"
#include "DrawType.h"
#include "IRenderContext.h"
#include "IResourceContext.h"
#include "ResourceId.h"
#include "ResourceValidation.h"
#include "consts.h"
#include "init_types.h"

namespace rendell {
IndexBufferId createIndexBuffer(const index_t *data, size_t size);
IndexBufferId createIndexBuffer(const IndexContainer &data);
DynamicIndexBufferId createDynamicIndexBuffer(size_t size);
VertexBufferId createVertexBuffer(const vertex_t *data, size_t size);
VertexBufferId createVertexBuffer(const VertexContainer &data);
VertexBufferId createDynamicVertexBuffer(size_t size);
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
FragmentShaderId createFragmentShader(const std::string &src, ResultCallback callback = nullptr);
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
void setSubData(Texture2DArrayId texture2DArrayId, uint32_t index, uint32_t width, uint32_t height,
                TextureFormat textureFormat, const byte_t *pixels, uint32_t widthOffset = 0,
                uint32_t heightOffset = 0);

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

void setClearBits(bitfield bits);
void setClearColor(float r, float g, float b, float a);
void setClearColor(Color color);
void setViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height);
void setScissors(int x, int y, int width, int height);
void setDrawType(DrawMode drawMode, PrimitiveTopology primitiveTopology,
                 uint32_t instanceCount = 0);

void setShaderProgram(ShaderProgramId shaderProgramId);
void setVertexAssembly(VertexAssemblyId vertexAssemblyId);
void setShaderBuffer(ShaderBufferId shaderBufferId, uint32_t binding);
void setUniformBuffer(UniformBufferId uniformBufferId, uint32_t binding);
void setUniform(UniformInt1Id uniformId, int val);
void setUniform(UniformInt2Id uniformId, int val1, int val2);
void setUniform(UniformInt3Id uniformId, int val1, int val2, int val3);
void setUniform(UniformInt4Id uniformId, int val1, int val2, int val3, int val4);
void setUniform(UniformFloat1Id uniformId, float val1);
void setUniform(UniformFloat2Id uniformId, float val1, float val2);
void setUniform(UniformFloat3Id uniformId, float val1, float val2, float val3);
void setUniform(UniformFloat4Id uniformId, float val1, float val2, float val3, float val4);
void setUniform(UniformMat4Id uniformId, const float *data);
void setTexture2D(UniformSampler2DId uniformSamplerId, Texture2DId textureId, uint32_t stage);
void setTexture2D(UniformSampler2DId uniformSamplerId, Texture2DArrayId textureId, uint32_t stage);

void submit();
void submit(ShaderProgramId shaderProgramId);
void submit(DrawMode drawMode, PrimitiveTopology primitiveTopology);

IResourceContext *beginResourceCommands();
void endResourceCommands(IResourceContext *resourceContext);
void endResourceCommands(IResourceContext *resourceContext, NativeViewId nativeViewid);

IRenderContext *beginRenderCommands();
void endRenderCommands(IRenderContext *renderContext);
void endRenderCommands(IRenderContext *renderContext, NativeViewId nativeViewId);

void renderFrame();
void renderFrame(NativeViewId nativeFrameId);

} // namespace rendell