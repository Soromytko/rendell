#include <ResourceContext.h>

#include <CallbackTable.h>
#include <Command.h>
#include <DataContainerStorage.h>
#include <DrawCallState.h>
#include <ResourceIdStorages.h>
#include <rendell/ResourceValidation.h>
#include <rendell/hash.h>

#include <logging.h>

#include <cassert>

namespace rendell {
ResourceContext::ResourceContext() {
    _resourceDataProvider = makeResourceDataProvider();
}

IndexBufferId ResourceContext::createIndexBuffer(const index_t *data, size_t size) {
    assert(data);
    return createIndexBuffer(IndexContainer(data, size));
}

IndexBufferId ResourceContext::createIndexBuffer(const IndexContainer &data) {
    CreateIndexBufferCmdData cmdData;
    cmdData.id = getIndexBufferIdStorage().alloc();
    cmdData.isDynamic = false;
    cmdData.dataSize = data.getSize();
    cmdData.dataKey = _resourceDataProvider->indexBufferDataContainerStorage.store(data);
    _resourceCommandBuffer << cmdData.type << cmdData;
    return cmdData.id;
}

DynamicIndexBufferId ResourceContext::createDynamicIndexBuffer(size_t size) {
    assert(size > 0);
    CreateIndexBufferCmdData cmdData;
    cmdData.id = getIndexBufferIdStorage().alloc();
    cmdData.isDynamic = true;
    cmdData.dataSize = size;
    cmdData.dataKey = 0;
    _resourceCommandBuffer << cmdData.type << cmdData;
    return static_cast<DynamicIndexBufferId>(cmdData.id);
}

VertexBufferId ResourceContext::createVertexBuffer(const vertex_t *data, size_t size) {
    assert(data);
    return createVertexBuffer(VertexContainer(data, size));
}

VertexBufferId ResourceContext::createVertexBuffer(const VertexContainer &data) {
    CreateVertexBufferCmdData cmdData;
    cmdData.id = getVertexBufferIdStorage().alloc();
    cmdData.isDynamic = false;
    cmdData.dataSize = data.getSize();
    cmdData.dataKey = _resourceDataProvider->vertexBufferDataContainerStorage.store(data);
    _resourceCommandBuffer << cmdData.type << cmdData;
    return cmdData.id;
}

DynamicVertexBufferId ResourceContext::createDynamicVertexBuffer(size_t size) {
    CreateVertexBufferCmdData cmdData;
    cmdData.id = getVertexBufferIdStorage().alloc();
    cmdData.isDynamic = true;
    cmdData.dataSize = size;
    cmdData.dataKey = 0;
    _resourceCommandBuffer << cmdData.type << cmdData;
    return static_cast<DynamicVertexBufferId>(cmdData.id);
}

UniformBufferId ResourceContext::createUniformBuffer(const byte_t *data, size_t size) {
    assert(data);
    return createUniformBuffer(ByteContainer(data, size));
}

UniformBufferId ResourceContext::createUniformBuffer(const ByteContainer &data) {
    CreateUniformBufferCmdData cmdData;
    cmdData.id = getUniformBufferIdStorage().alloc();
    cmdData.dataKey = _resourceDataProvider->byteContainerStorage.store(data);
    _resourceCommandBuffer << cmdData.type << cmdData;
    return cmdData.id;
}

ShaderBufferId ResourceContext::createShaderBuffer(const byte_t *data, size_t size) {
    assert(data);
    assert(size > 0);
    return createShaderBuffer(ByteContainer(data, size));
}

ShaderBufferId ResourceContext::createShaderBuffer(const ByteContainer &data) {
    CreateShaderBufferCmdData cmdData;
    cmdData.id = getShaderBufferIdStorage().alloc();
    cmdData.dataSize = data.getSize();
    cmdData.dataKey = _resourceDataProvider->byteContainerStorage.store(data);
    _resourceCommandBuffer << cmdData.type << cmdData;
    return cmdData.id;
}

ShaderBufferId ResourceContext::createShaderBuffer(size_t size) {
    assert(size > 0);
    CreateShaderBufferCmdData cmdData;
    cmdData.id = getShaderBufferIdStorage().alloc();
    cmdData.dataKey = 0;
    _resourceCommandBuffer << cmdData.type << cmdData;
    return cmdData.id;
}

VertexAssemblyId
ResourceContext::createVertexAssembly(IndexBufferId indexBufferId,
                                      const std::vector<VertexBufferId> &vertexBufferIds,
                                      const std::vector<VertexLayout> &vertexLayouts) {
    CreateVertexAssemblyCmdData cmdData;
    cmdData.id = getVertexAssemblyIdStorage().alloc();
    cmdData.indexBufferId = indexBufferId;

    cmdData.vertexBufferIdsKey = _resourceDataProvider->vertexBufferIdsContainerStorage.store(
        {vertexBufferIds.data(), vertexBufferIds.size()});
    cmdData.vertexLayoutsKey = _resourceDataProvider->vertexLayoutsContainerStorage.store(
        {vertexLayouts.data(), vertexLayouts.size()});
    _resourceCommandBuffer << cmdData.type << cmdData;
    return cmdData.id;
}

Texture2DId ResourceContext::createTexture2D(uint32_t width, uint32_t height, TextureFormat format,
                                             const byte_t *pixels) {
    assert(pixels);
    CreateTexture2DCmdData cmdData;
    cmdData.id = getTexture2DIdStorage().alloc();
    cmdData.width = width;
    cmdData.height = height;
    cmdData.format = format;
    cmdData.dataKey = _resourceDataProvider->byteContainerStorage.store(
        ByteContainer(pixels, width * height * getTextureFormatSize(format)));
    _resourceCommandBuffer << cmdData.type << cmdData;
    return cmdData.id;
}

Texture2DArrayId ResourceContext::createTexture2DArray(uint32_t width, uint32_t height,
                                                       uint32_t count, TextureFormat format) {
    CreateTexture2DArrayCmdData cmdData;
    cmdData.id = getTexture2DArrayIdStorage().alloc();
    cmdData.width = width;
    cmdData.height = height;
    cmdData.count = count;
    cmdData.format = format;
    _resourceCommandBuffer << cmdData.type << cmdData;
    return cmdData.id;
}

VertexShaderId ResourceContext::createVertexShader(const std::string &src,
                                                   ResultCallback callback) {
    CreateVertexShaderCmdData cmdData;
    cmdData.id = getVertexShaderIdStorage().alloc();
    cmdData.srcKey = _resourceDataProvider->stringContainerStorage.store(
        StringContainer(src.data(), src.length() + 1));
    _resourceCommandBuffer << cmdData.type << cmdData;
    if (callback) {
        getResultCallbackTable().add(hash(cmdData.id), callback);
    }
    return cmdData.id;
}

FragmentShaderId ResourceContext::createFragmentShader(const std::string &src,
                                                       ResultCallback callback) {
    CreateFragmentShaderCmdData cmdData;
    cmdData.id = getFragmentShaderIdStorage().alloc();
    cmdData.srcKey = _resourceDataProvider->stringContainerStorage.store(
        StringContainer(src.data(), src.length() + 1));
    _resourceCommandBuffer << cmdData.type << cmdData;
    if (callback) {
        getResultCallbackTable().add(hash(cmdData.id), callback);
    }
    return cmdData.id;
}

ShaderProgramId ResourceContext::createShaderProgram(VertexShaderId vertexShaderId,
                                                     FragmentShaderId fragmentShaderId,
                                                     ResultCallback callback) {
    CreateShaderProgramCmdData cmdData;
    cmdData.id = getShaderProgramIdStorage().alloc();
    cmdData.vertexShaderId = vertexShaderId;
    cmdData.fragmentShaderId = fragmentShaderId;
    _resourceCommandBuffer << cmdData.type << cmdData;
    if (callback) {
        getResultCallbackTable().add(hash(cmdData.id), callback);
    }
    return cmdData.id;
}

UniformId ResourceContext::createUniform(const std::string &name, UniformType type) {
    CreateUniformCmdData cmdData;
    cmdData.id = getUniformIdStorage().alloc();
    cmdData.dataType = type;
    cmdData.nameKey = _resourceDataProvider->stringContainerStorage.store(
        StringContainer(name.data(), name.length() + 1));
    _resourceCommandBuffer << cmdData.type << cmdData;
    return cmdData.id;
}

UniformInt1Id ResourceContext::createUniformInt1(const std::string &name) {
    assert(!name.empty());
    UniformId id = createUniform(name, UniformType::int1);
    return static_cast<UniformInt1Id>(id);
}

UniformInt2Id ResourceContext::createUniformInt2(const std::string &name) {
    assert(!name.empty());
    UniformId id = createUniform(name, UniformType::int2);
    return static_cast<UniformInt2Id>(id);
}

UniformInt3Id ResourceContext::createUniformInt3(const std::string &name) {
    assert(!name.empty());
    UniformId id = createUniform(name, UniformType::int3);
    return static_cast<UniformInt3Id>(id);
}

UniformInt4Id ResourceContext::createUniformInt4(const std::string &name) {
    assert(!name.empty());
    UniformId id = createUniform(name, UniformType::int4);
    return static_cast<UniformInt4Id>(id);
}

UniformFloat1Id ResourceContext::createUniformFloat1(const std::string &name) {
    assert(!name.empty());
    UniformId id = createUniform(name, UniformType::float1);
    return static_cast<UniformFloat1Id>(id);
}

UniformFloat2Id ResourceContext::createUniformFloat2(const std::string &name) {
    assert(!name.empty());
    UniformId id = createUniform(name, UniformType::float2);
    return static_cast<UniformFloat2Id>(id);
}

UniformFloat3Id ResourceContext::createUniformFloat3(const std::string &name) {
    assert(!name.empty());
    UniformId id = createUniform(name, UniformType::float3);
    return static_cast<UniformFloat3Id>(id);
}

UniformFloat4Id ResourceContext::createUniformFloat4(const std::string &name) {
    assert(!name.empty());
    UniformId id = createUniform(name, UniformType::float4);
    return static_cast<UniformFloat4Id>(id);
}

UniformMat4Id ResourceContext::createUniformMat4(const std::string &name) {
    UniformId id = createUniform(name, UniformType::mat4);
    assert(!name.empty());
    return static_cast<UniformMat4Id>(id);
}

UniformSampler2DId ResourceContext::createUniformSampler2D(const std::string &name) {
    assert(!name.empty());
    UniformId id = createUniform(name, UniformType::sampler2D);
    return static_cast<UniformSampler2DId>(id);
}

void ResourceContext::setSubData(DynamicIndexBufferId dynamicIndexBufferId, const index_t *data,
                                 size_t size, size_t offset) {
    assert(data);
    SetIndexBufferSubDataCmdData cmdData;
    cmdData.id = dynamicIndexBufferId;
    cmdData.offset = offset;
    cmdData.dataKey =
        _resourceDataProvider->indexBufferDataContainerStorage.store(IndexContainer(data, size));
    _resourceCommandBuffer << cmdData.type << cmdData;
}

void ResourceContext::setSubData(DynamicVertexBufferId dynamicVertexBufferId, const vertex_t *data,
                                 size_t size, size_t offset) {
    assert(data);
    SetVertexBufferSubDataCmdData cmdData;
    cmdData.id = dynamicVertexBufferId;
    cmdData.offset = offset;
    cmdData.dataKey =
        _resourceDataProvider->vertexBufferDataContainerStorage.store(VertexContainer(data, size));
    _resourceCommandBuffer << cmdData.type << cmdData;
}

void ResourceContext::setSubData(ShaderBufferId shaderBufferId, const byte_t *data, size_t size,
                                 size_t offset) {
    assert(data);
    SetShaderBufferSubDataCmdData cmdData;
    cmdData.id = shaderBufferId;
    cmdData.offset = offset;
    cmdData.dataKey = _resourceDataProvider->byteContainerStorage.store(ByteContainer(data, size));
    _resourceCommandBuffer << cmdData.type << cmdData;
}

void ResourceContext::setSubData(Texture2DId texture2DId, uint32_t width, uint32_t height,
                                 TextureFormat textureFormat, const byte_t *pixels,
                                 uint32_t widthOffset, uint32_t heightOffset) {
    assert(pixels);
    assert(width > 0);
    assert(height > 0);
    SetTexture2DSubDataCmdData cmdData;
    cmdData.id = texture2DId;
    cmdData.width = width;
    cmdData.height = height;
    cmdData.widthOffset = widthOffset;
    cmdData.heightOffset = heightOffset;
    cmdData.dataKey = _resourceDataProvider->byteContainerStorage.store(
        ByteContainer(pixels, width * height * getTextureFormatSize(textureFormat)));
    _resourceCommandBuffer << cmdData.type << cmdData;
}

void ResourceContext::setSubData(Texture2DArrayId texture2DArrayId, uint32_t index, uint32_t width,
                                 uint32_t height, TextureFormat textureFormat, const byte_t *pixels,
                                 uint32_t widthOffset, uint32_t heightOffset) {
    assert(pixels);
    assert(width > 0);
    assert(height > 0);
    SetTexture2DArraySubDataCmdData cmdData;
    cmdData.id = texture2DArrayId;
    cmdData.index = index;
    cmdData.width = width;
    cmdData.height = height;
    cmdData.widthOffset = widthOffset;
    cmdData.heightOffset = heightOffset;
    cmdData.dataKey = _resourceDataProvider->byteContainerStorage.store(
        ByteContainer(pixels, width * height * getTextureFormatSize(textureFormat)));
    _resourceCommandBuffer << cmdData.type << cmdData;
}

void ResourceContext::destroy(IndexBufferId indexBufferId) {
    assert(isValid(indexBufferId));
    if (!getIndexBufferIdStorage().free(indexBufferId)) {
        // TODO: Warning
        return;
    }
    DestroyIndexBufferCmdData cmdData;
    cmdData.id = indexBufferId;
    _resourceCommandBuffer << cmdData.type << cmdData;
}

void ResourceContext::destroy(VertexBufferId vertexBufferId) {
    assert(isValid(vertexBufferId));
    if (!getVertexBufferIdStorage().free(vertexBufferId)) {
        // TODO: Warning
        return;
    }
    DestroyVertexBufferCmdData cmdData;
    cmdData.id = vertexBufferId;
    _resourceCommandBuffer << cmdData.type << cmdData;
}

void ResourceContext::destroy(UniformBufferId uniformBufferId) {
    assert(isValid(uniformBufferId));
    if (!getUniformBufferIdStorage().free(uniformBufferId)) {
        // TODO: Warning
        return;
    }
    DestroyUniformBufferCmdData cmdData;
    cmdData.id = uniformBufferId;
    _resourceCommandBuffer << cmdData.type << cmdData;
}

void ResourceContext::destroy(ShaderBufferId shaderBufferId) {
    assert(isValid(shaderBufferId));
    if (!getShaderBufferIdStorage().free(shaderBufferId)) {
        // TODO: Warning
        return;
    }
    DestroyShaderBufferCmdData cmdData;
    cmdData.id = shaderBufferId;
    _resourceCommandBuffer << cmdData.type << cmdData;
}

void ResourceContext::destroy(VertexAssemblyId vertexAssemblyId) {
    assert(isValid(vertexAssemblyId));
    if (!getVertexAssemblyIdStorage().free(vertexAssemblyId)) {
        // TODO: Warning
        return;
    }
    DestroyVertexAssemblyCmdData cmdData;
    cmdData.id = vertexAssemblyId;
    _resourceCommandBuffer << cmdData.type << cmdData;
}

void ResourceContext::destroy(Texture2DId texture2DId) {
    assert(isValid(texture2DId));
    if (!getTexture2DIdStorage().free(texture2DId)) {
        // TODO: Warning
        return;
    }
    DestroyTexture2DCmdData cmdData;
    cmdData.id = texture2DId;
    _resourceCommandBuffer << cmdData.type << cmdData;
}

void ResourceContext::destroy(Texture2DArrayId texture2DArrayId) {
    assert(isValid(texture2DArrayId));
    if (!getTexture2DArrayIdStorage().free(texture2DArrayId)) {
        // TODO: Warning
        return;
    }
    DestroyTexture2DArrayCmdData cmdData;
    cmdData.id = texture2DArrayId;
    _resourceCommandBuffer << cmdData.type << cmdData;
}

void ResourceContext::destroy(VertexShaderId vertexShaderId) {
    assert(isValid(vertexShaderId));
    if (!getVertexShaderIdStorage().free(vertexShaderId)) {
        // TODO: Warning
        return;
    }
    DestroyVertexShaderCmdData cmdData;
    cmdData.id = vertexShaderId;
    _resourceCommandBuffer << cmdData.type << cmdData;
}

void ResourceContext::destroy(FragmentShaderId fragmentShaderId) {
    assert(isValid(fragmentShaderId));
    if (!getFragmentShaderIdStorage().free(fragmentShaderId)) {
        // TODO: Warning
        return;
    }
    DestroyFragmentShaderCmdData cmdData;
    cmdData.id = fragmentShaderId;
    _resourceCommandBuffer << cmdData.type << cmdData;
}

void ResourceContext::destroy(ShaderProgramId shaderProgramId) {
    assert(isValid(shaderProgramId));
    if (!getShaderProgramIdStorage().free(shaderProgramId)) {
        // TODO: Warning
        return;
    }
    DestroyShaderProgramCmdData cmdData;
    cmdData.id = shaderProgramId;
    _resourceCommandBuffer << cmdData.type << cmdData;
}

void ResourceContext::destroy(UniformId uniformId) {
    assert(isValid(uniformId));
    if (!getUniformIdStorage().free(uniformId)) {
        // TODO: Warning
        return;
    }
}

const ByteBuffer &ResourceContext::getCommandBuffer() const {
    return _resourceCommandBuffer;
}

ResourceDataProviderSharedPtr ResourceContext::getResourceDataProvider() const {
    return _resourceDataProvider;
}

void ResourceContext::reset() {
    _resourceCommandBuffer.reset();
}
} // namespace rendell
