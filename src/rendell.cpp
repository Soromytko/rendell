#include <rendell/rendell.h>

#include <Command.h>
#include <RenderPipelineStorage.h>
#include <logging.h>
#include <rendell/DataType.h>

#include <ContextPool.h>

#include "RenderContext.h"
#include "RenderPipeline.h"
#include "ResourceContext.h"

#include <memory>

// Static data
namespace rendell {
using ResourceContextPool = ContextPool<ResourceContext>;
using RenderContextPool = ContextPool<RenderContext>;

static ResourceContextPool s_resourceContextPool(config::resourceContextPoolSize);
static RenderContextPool s_renderContextPool(config::renderContextPoolSize);

static std::unique_ptr<ResourceContext> s_resourceContext{nullptr};
static std::unique_ptr<RenderContext> s_renderContext{nullptr};

static const std::unique_ptr<ResourceContext> &getMainThreadResourceContext() {
    if (!s_resourceContext) {
        s_resourceContext = s_resourceContextPool.getContext();
    }
    assert(s_resourceContext);
    return s_resourceContext;
}

static const std::unique_ptr<RenderContext> &getMainThreadRenderContext() {
    if (!s_renderContext) {
        s_renderContext = s_renderContextPool.getContext();
    }
    assert(s_renderContext);
    return s_renderContext;
}

template <typename ToResource, typename FromResource>
static std::unique_ptr<ToResource> castResource(std::unique_ptr<FromResource> context) {
    assert(dynamic_cast<ToResource *>(context.get()) != nullptr);
    return std::unique_ptr<ToResource>(static_cast<ToResource *>(context.release()));
}

static RenderPipeline *getRenderPipeline(NativeViewId nativeViewid);
static void submitResourceContext(RenderPipeline *renderPipeline,
                                  std::unique_ptr<ResourceContext> resourceContext);
static void submitRenderContext(RenderPipeline *renderPipeline,
                                std::unique_ptr<RenderContext> renderContext);

static void endResourceCommands(std::unique_ptr<IResourceContext> resourceContext,
                                NativeViewId nativeViewid) {
    auto casted = castResource<ResourceContext>(std::move(resourceContext));
    submitResourceContext(getRenderPipeline(nativeViewid), std::move(casted));
}

static void endRenderCommands(std::unique_ptr<IRenderContext> renderContext,
                              NativeViewId nativeViewid) {
    auto casted = castResource<RenderContext>(std::move(renderContext));
    submitRenderContext(getRenderPipeline(nativeViewid), std::move(casted));
}
} // namespace rendell

// Implementation
namespace rendell {
static NativeViewId getMainNativeViewId();

void ContextWrapper<IResourceContext>::end() {
    if (_context) {
        const NativeViewId nativeViewId = getMainNativeViewId();
        endResourceCommands(std::move(_context), nativeViewId);
    }
}

void ContextWrapper<IResourceContext>::end(NativeViewId nativeViewId) {
    if (_context) {
        endResourceCommands(std::move(_context), nativeViewId);
    }
}

void ContextWrapper<IRenderContext>::end() {
    if (_context) {
        const NativeViewId nativeViewId = getMainNativeViewId();
        endRenderCommands(std::move(_context), nativeViewId);
    }
}

void ContextWrapper<IRenderContext>::end(NativeViewId nativeViewId) {
    if (_context) {
        endRenderCommands(std::move(_context), nativeViewId);
    }
}

static void submitResourceContext(RenderPipeline *renderPipeline,
                                  std::unique_ptr<ResourceContext> resourceContext) {
    assert(renderPipeline);
    assert(resourceContext);
    renderPipeline->submitResourceContext(std::move(resourceContext));
    renderPipeline->setResourceContextReleasedCallback(
        [](std::unique_ptr<ResourceContext> releasedResourceContext) {
            s_resourceContextPool.returnContext(std::move(releasedResourceContext));
        });
}

static void submitRenderContext(RenderPipeline *renderPipeline,
                                std::unique_ptr<RenderContext> renderContext) {
    assert(renderPipeline);
    assert(renderContext);
    renderPipeline->submitRenderContext(std::move(renderContext));
    renderPipeline->setRenderContextReleasedCallback(
        [](std::unique_ptr<RenderContext> releasedRenderContext) {
            s_renderContextPool.returnContext(std::move(releasedRenderContext));
        });
}

IndexBufferId createIndexBuffer(const index_t *data, size_t size) {
    assert(data);
    return getMainThreadResourceContext()->createIndexBuffer(data, size);
}

IndexBufferId createIndexBuffer(const IndexContainer &data) {
    return getMainThreadResourceContext()->createIndexBuffer(data);
}

DynamicIndexBufferId createDynamicIndexBuffer(size_t size) {
    assert(size > 0);
    return getMainThreadResourceContext()->createDynamicIndexBuffer(size);
}

VertexBufferId createVertexBuffer(const vertex_t *data, size_t size) {
    assert(data);
    return getMainThreadResourceContext()->createVertexBuffer(data, size);
}

VertexBufferId createVertexBuffer(const VertexContainer &data) {
    return getMainThreadResourceContext()->createVertexBuffer(data);
}

VertexBufferId createDynamicVertexBuffer(size_t size) {
    assert(size);
    return getMainThreadResourceContext()->createDynamicVertexBuffer(size);
}

UniformBufferId createUniformBuffer(const byte_t *data, size_t size) {
    assert(data);
    return getMainThreadResourceContext()->createUniformBuffer(data, size);
}

UniformBufferId createUniformBuffer(const ByteContainer &data) {
    return getMainThreadResourceContext()->createUniformBuffer(data);
}

ShaderBufferId createShaderBuffer(const byte_t *data, size_t size) {
    assert(data);
    assert(size > 0);
    return getMainThreadResourceContext()->createShaderBuffer(data, size);
}

ShaderBufferId createShaderBuffer(const ByteContainer &data) {
    return getMainThreadResourceContext()->createShaderBuffer(data);
}

ShaderBufferId createShaderBuffer(size_t size) {
    assert(size > 0);
    return getMainThreadResourceContext()->createShaderBuffer(size);
}

VertexAssemblyId createVertexAssembly(IndexBufferId indexBufferId,
                                      const std::vector<VertexBufferId> &vertexBufferIds,
                                      const std::vector<VertexLayout> &vertexLayouts) {
    return getMainThreadResourceContext()->createVertexAssembly(indexBufferId, vertexBufferIds,
                                                                vertexLayouts);
}

Texture2DId createTexture2D(uint32_t width, uint32_t height, TextureFormat format,
                            const byte_t *pixels) {
    assert(pixels);
    return getMainThreadResourceContext()->createTexture2D(width, height, format, pixels);
}

Texture2DArrayId createTexture2DArray(uint32_t width, uint32_t height, uint32_t count,
                                      TextureFormat format) {
    return getMainThreadResourceContext()->createTexture2DArray(width, height, count, format);
}

VertexShaderId createVertexShader(const std::string &src, ResultCallback callback) {
    return getMainThreadResourceContext()->createVertexShader(src, callback);
}

FragmentShaderId createFragmentShader(const std::string &src, ResultCallback callback) {
    return getMainThreadResourceContext()->createFragmentShader(src, callback);
}

ShaderProgramId createShaderProgram(VertexShaderId vertexShaderId,
                                    FragmentShaderId fragmentShaderId, ResultCallback callback) {
    return getMainThreadResourceContext()->createShaderProgram(vertexShaderId, fragmentShaderId,
                                                               callback);
}

UniformId createUniform(const std::string &name, UniformType type) {
    assert(!name.empty());
    return getMainThreadResourceContext()->createUniform(name, type);
}

UniformInt1Id createUniformInt1(const std::string &name) {
    assert(!name.empty());
    return getMainThreadResourceContext()->createUniformInt1(name);
}

UniformInt2Id createUniformInt2(const std::string &name) {
    return getMainThreadResourceContext()->createUniformInt2(name);
}

UniformInt3Id createUniformInt3(const std::string &name) {
    assert(!name.empty());
    return getMainThreadResourceContext()->createUniformInt3(name);
}

UniformInt4Id createUniformInt4(const std::string &name) {
    assert(!name.empty());
    return getMainThreadResourceContext()->createUniformInt4(name);
}

UniformFloat1Id createUniformFloat1(const std::string &name) {
    assert(!name.empty());
    return getMainThreadResourceContext()->createUniformFloat1(name);
}

UniformFloat2Id createUniformFloat2(const std::string &name) {
    assert(!name.empty());
    return getMainThreadResourceContext()->createUniformFloat2(name);
}

UniformFloat3Id createUniformFloat3(const std::string &name) {
    return getMainThreadResourceContext()->createUniformFloat3(name);
}

UniformFloat4Id createUniformFloat4(const std::string &name) {
    assert(!name.empty());
    return getMainThreadResourceContext()->createUniformFloat4(name);
}

UniformMat4Id createUniformMat4(const std::string &name) {
    assert(!name.empty());
    return getMainThreadResourceContext()->createUniformMat4(name);
}

UniformSampler2DId createUniformSampler2D(const std::string &name) {
    assert(!name.empty());
    return getMainThreadResourceContext()->createUniformSampler2D(name);
}

void setSubData(DynamicIndexBufferId dynamicIndexBufferId, const index_t *data, size_t size,
                size_t offset) {
    assert(data);
    getMainThreadResourceContext()->setSubData(dynamicIndexBufferId, data, size, offset);
}

void setSubData(DynamicVertexBufferId dynamicVertexBufferId, const vertex_t *data, size_t size,
                size_t offset) {
    assert(data);
    getMainThreadResourceContext()->setSubData(dynamicVertexBufferId, data, size, offset);
}

void setSubData(ShaderBufferId shaderBufferId, const byte_t *data, size_t size, size_t offset) {
    assert(data);
    getMainThreadResourceContext()->setSubData(shaderBufferId, data, size, offset);
}

void setSubData(Texture2DId texture2DId, uint32_t width, uint32_t height,
                TextureFormat textureFormat, const byte_t *pixels, uint32_t widthOffset,
                uint32_t heightOffset) {
    assert(width > 0);
    assert(height > 0);
    assert(pixels);
    getMainThreadResourceContext()->setSubData(texture2DId, width, height, textureFormat, pixels,
                                               widthOffset, heightOffset);
}

void setSubData(Texture2DArrayId texture2DArrayId, uint32_t index, uint32_t width, uint32_t height,
                TextureFormat textureFormat, const byte_t *pixels, uint32_t widthOffset,
                uint32_t heightOffset) {
    assert(width > 0);
    assert(height > 0);
    assert(pixels);
    getMainThreadResourceContext()->setSubData(texture2DArrayId, index, width, height,
                                               textureFormat, pixels, widthOffset, heightOffset);
}

void destroy(IndexBufferId indexBufferId) {
    getMainThreadResourceContext()->destroy(indexBufferId);
}

void destroy(VertexBufferId vertexBufferId) {
    getMainThreadResourceContext()->destroy(vertexBufferId);
}

void destroy(UniformBufferId uniformBufferId) {
    getMainThreadResourceContext()->destroy(uniformBufferId);
}

void destroy(ShaderBufferId shaderBufferId) {
    getMainThreadResourceContext()->destroy(shaderBufferId);
}

void destroy(VertexAssemblyId vertexAssemblyId) {
    getMainThreadResourceContext()->destroy(vertexAssemblyId);
}

void destroy(Texture2DId texture2DId) {
    getMainThreadResourceContext()->destroy(texture2DId);
}

void destroy(Texture2DArrayId texture2DArrayId) {
    getMainThreadResourceContext()->destroy(texture2DArrayId);
}

void destroy(VertexShaderId vertexShaderId) {
    getMainThreadResourceContext()->destroy(vertexShaderId);
}

void destroy(FragmentShaderId fragmentShaderId) {
    getMainThreadResourceContext()->destroy(fragmentShaderId);
}

void destroy(ShaderProgramId shaderProgramId) {
    getMainThreadResourceContext()->destroy(shaderProgramId);
}

void destroy(UniformId uniformId) {
    getMainThreadResourceContext()->destroy(uniformId);
}

void setClearBits(bitfield bits) {
    getMainThreadRenderContext()->setClearBits(bits);
}

void setClearColor(float r, float g, float b, float a) {
    getMainThreadRenderContext()->setClearColor(r, g, b, a);
}

void setClearColor(Color color) {
    getMainThreadRenderContext()->setClearColor(color);
}

void setViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) {
    getMainThreadRenderContext()->setViewport(x, y, width, height);
}

void setScissors(int x, int y, int width, int height) {
    getMainThreadRenderContext()->setScissors(x, y, width, height);
}

void setVertexCount(uint32_t count) {
    getMainThreadRenderContext()->setVertexCount(count);
}

void setDrawType(DrawMode drawMode, PrimitiveTopology primitiveTopology, uint32_t instanceCount) {
    getMainThreadRenderContext()->setDrawType(drawMode, primitiveTopology, instanceCount);
}

void setShaderProgram(ShaderProgramId shaderProgramId) {
    assert(isValid(shaderProgramId));
    getMainThreadRenderContext()->setShaderProgram(shaderProgramId);
}

void setVertexAssembly(VertexAssemblyId vertexAssemblyId) {
    assert(isValid(vertexAssemblyId));
    getMainThreadRenderContext()->setVertexAssembly(vertexAssemblyId);
}

void setShaderBuffer(ShaderBufferId shaderBufferId, uint32_t binding) {
    assert(isValid(shaderBufferId));
    getMainThreadRenderContext()->setShaderBuffer(shaderBufferId, binding);
}

void setUniformBuffer(UniformBufferId uniformBufferId, uint32_t binding) {
    assert(isValid(uniformBufferId));
    getMainThreadRenderContext()->setUniformBuffer(uniformBufferId, binding);
}

void setUniform(UniformInt1Id uniformId, int val) {
    assert(isValid(uniformId));
    getMainThreadRenderContext()->setUniform(uniformId, val);
}

void setUniform(UniformInt2Id uniformId, int val1, int val2) {
    assert(isValid(uniformId));
    getMainThreadRenderContext()->setUniform(uniformId, val1, val2);
}

void setUniform(UniformInt3Id uniformId, int val1, int val2, int val3) {
    assert(isValid(uniformId));
    getMainThreadRenderContext()->setUniform(uniformId, val1, val2, val3);
}

void setUniform(UniformInt4Id uniformId, int val1, int val2, int val3, int val4) {
    assert(isValid(uniformId));
    getMainThreadRenderContext()->setUniform(uniformId, val1, val2, val3, val4);
}

void setUniform(UniformFloat1Id uniformId, float val1) {
    assert(isValid(uniformId));
    getMainThreadRenderContext()->setUniform(uniformId, val1);
}

void setUniform(UniformFloat2Id uniformId, float val1, float val2) {
    assert(isValid(uniformId));
    getMainThreadRenderContext()->setUniform(uniformId, val1, val2);
}

void setUniform(UniformFloat3Id uniformId, float val1, float val2, float val3) {
    assert(isValid(uniformId));
    getMainThreadRenderContext()->setUniform(uniformId, val1, val2, val3);
}

void setUniform(UniformFloat4Id uniformId, float val1, float val2, float val3, float val4) {
    assert(isValid(uniformId));
    getMainThreadRenderContext()->setUniform(uniformId, val1, val2, val3, val4);
}

void setUniform(UniformMat4Id uniformId, const float *data) {
    assert(isValid(uniformId));
    getMainThreadRenderContext()->setUniform(uniformId, data);
}

void setTexture2D(UniformSampler2DId uniformSamplerId, Texture2DId textureId, uint32_t stage) {
    assert(isValid(uniformSamplerId));
    assert(isValid(textureId));
    getMainThreadRenderContext()->setTexture2D(uniformSamplerId, textureId, stage);
}

void setTexture2D(UniformSampler2DId uniformSamplerId, Texture2DArrayId textureId, uint32_t stage) {
    assert(isValid(uniformSamplerId));
    assert(isValid(textureId));
    getMainThreadRenderContext()->setTexture2D(uniformSamplerId, textureId, stage);
}

void submit() {
    getMainThreadRenderContext()->submit();
}

void submit(ShaderProgramId shaderProgramId) {
    getMainThreadRenderContext()->submit(shaderProgramId);
}

void submit(DrawMode drawMode, PrimitiveTopology primitiveTopology) {
    getMainThreadRenderContext()->submit(drawMode, primitiveTopology);
}

static NativeViewId getMainNativeViewId() {
    const std::vector<NativeViewId> nativeViewIds =
        RenderPipelineStorage::getInstance()->getNativeViewIds();
    assert(nativeViewIds.size() > 0);
    return nativeViewIds[0];
}

static RenderPipeline *getRenderPipeline(NativeViewId nativeViewid) {
    RenderPipeline *result = RenderPipelineStorage::getInstance()->getRenderPipeline(nativeViewid);
    assert(result);
    return result;
}

ResourceContextWrapper beginResourceCommands() {
    auto resourceContext = s_resourceContextPool.getContext();
    assert(resourceContext);
    return ResourceContextWrapper(std::move(resourceContext));
}

RenderContextWrapper beginRenderCommands() {
    auto renderContext = s_renderContextPool.getContext();
    assert(renderContext);
    return RenderContextWrapper(std::move(renderContext));
}

void renderFrame() {
    const NativeViewId nativeViewId = getMainNativeViewId();
    renderFrame(nativeViewId);
}

void renderFrame(NativeViewId nativeViewId) {
    RenderPipeline *renderPipeline =
        RenderPipelineStorage::getInstance()->getRenderPipeline(nativeViewId);

    if (s_resourceContext) {
        submitResourceContext(renderPipeline, std::move(s_resourceContext));
        s_resourceContext = nullptr;
    }

    if (s_renderContext) {
        submitRenderContext(renderPipeline, std::move(s_renderContext));
        s_renderContext = nullptr;
    }

    renderPipeline->waitAndRender();
}

} // namespace rendell
