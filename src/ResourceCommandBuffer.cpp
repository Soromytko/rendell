#include <rendell/ResourceCommandBuffer.h>

#include <CallbackTable.h>
#include <Command.h>
#include <DataContainerStorage.h>
#include <rendell/hash.h>

#include <ResourceCommandBufferImpl.h>
#include <ResourceIdsAllocator.h>

#include <cassert>

#define IMPL getImpl(_implStorage)

namespace rendell {
inline static ResourceCommandBufferImpl &getImpl(std::byte *storage) noexcept {
    return *reinterpret_cast<ResourceCommandBufferImpl *>(storage);
}

inline static const ResourceCommandBufferImpl &getImpl(const std::byte *storage) noexcept {
    return *reinterpret_cast<const ResourceCommandBufferImpl *>(storage);
}

ResourceCommandBuffer::ResourceCommandBuffer(InstanceId instanceId, ResourceIdAllocator &allocator)
    : _instanceId(instanceId)
    , _allocator(allocator) {
    static_assert(sizeof(ResourceCommandBufferImpl) <= _implSize, "ImplSize is too small!");
    static_assert(alignof(ResourceCommandBufferImpl) == _implAlign, "ImplAlign mismatch!");

    new (_implStorage) ResourceCommandBufferImpl();
}

ResourceCommandBuffer::~ResourceCommandBuffer() {
    IMPL.~ResourceCommandBufferImpl();
}

IndexBufferId ResourceCommandBuffer::createIndexBuffer(const index_t *data, size_t size) {
    assert(data);
    return createIndexBuffer(IndexContainer(data, size));
}

IndexBufferId ResourceCommandBuffer::createIndexBuffer(const IndexContainer &data) {
    CreateIndexBufferCmdData cmdData;
    cmdData.id = _allocator.allocIndexBufferId();
    cmdData.isDynamic = false;
    cmdData.dataSize = data.getSize();
    cmdData.dataKey = IMPL.resourceDataProvider.indexBufferDataContainerStorage.store(data);
    IMPL.resourceCommandBuffer << cmdData.type << cmdData;
    return cmdData.id;
}

DynamicIndexBufferId ResourceCommandBuffer::createDynamicIndexBuffer(size_t size) {
    assert(size > 0);
    CreateIndexBufferCmdData cmdData;
    cmdData.id = _allocator.allocIndexBufferId();
    cmdData.isDynamic = true;
    cmdData.dataSize = size;
    cmdData.dataKey = 0;
    IMPL.resourceCommandBuffer << cmdData.type << cmdData;
    return static_cast<DynamicIndexBufferId>(cmdData.id);
}

VertexBufferId ResourceCommandBuffer::createVertexBuffer(const vertex_t *data, size_t size) {
    assert(data);
    return createVertexBuffer(VertexContainer(data, size));
}

VertexBufferId ResourceCommandBuffer::createVertexBuffer(const VertexContainer &data) {
    CreateVertexBufferCmdData cmdData;
    cmdData.id = _allocator.allocVertexBufferId();
    cmdData.isDynamic = false;
    cmdData.dataSize = data.getSize();
    cmdData.dataKey = IMPL.resourceDataProvider.vertexBufferDataContainerStorage.store(data);
    IMPL.resourceCommandBuffer << cmdData.type << cmdData;
    return cmdData.id;
}

DynamicVertexBufferId ResourceCommandBuffer::createDynamicVertexBuffer(size_t size) {
    CreateVertexBufferCmdData cmdData;
    cmdData.id = _allocator.allocVertexBufferId();
    cmdData.isDynamic = true;
    cmdData.dataSize = size;
    cmdData.dataKey = 0;
    IMPL.resourceCommandBuffer << cmdData.type << cmdData;
    return static_cast<DynamicVertexBufferId>(cmdData.id);
}

UniformBufferId ResourceCommandBuffer::createUniformBuffer(const byte_t *data, size_t size) {
    assert(data);
    return createUniformBuffer(ByteContainer(data, size));
}

UniformBufferId ResourceCommandBuffer::createUniformBuffer(const ByteContainer &data) {
    CreateUniformBufferCmdData cmdData;
    cmdData.id = _allocator.allocUniformBufferId();
    cmdData.dataKey = IMPL.resourceDataProvider.byteContainerStorage.store(data);
    IMPL.resourceCommandBuffer << cmdData.type << cmdData;
    return cmdData.id;
}

ShaderBufferId ResourceCommandBuffer::createShaderBuffer(const byte_t *data, size_t size) {
    assert(data);
    assert(size > 0);
    return createShaderBuffer(ByteContainer(data, size));
}

ShaderBufferId ResourceCommandBuffer::createShaderBuffer(const ByteContainer &data) {
    CreateShaderBufferCmdData cmdData;
    cmdData.id = _allocator.allocShaderBufferId();
    cmdData.dataSize = data.getSize();
    cmdData.dataKey = IMPL.resourceDataProvider.byteContainerStorage.store(data);
    IMPL.resourceCommandBuffer << cmdData.type << cmdData;
    return cmdData.id;
}

ShaderBufferId ResourceCommandBuffer::createShaderBuffer(size_t size) {
    assert(size > 0);
    CreateShaderBufferCmdData cmdData;
    cmdData.id = _allocator.allocShaderBufferId();
    cmdData.dataKey = 0;
    IMPL.resourceCommandBuffer << cmdData.type << cmdData;
    return cmdData.id;
}

VertexAssemblyId
ResourceCommandBuffer::createVertexAssembly(IndexBufferId indexBufferId,
                                            const std::vector<VertexBufferId> &vertexBufferIds,
                                            const std::vector<VertexLayout> &vertexLayouts) {
    CreateVertexAssemblyCmdData cmdData;
    cmdData.id = _allocator.allocVertexAssemblyId();
    cmdData.indexBufferId = indexBufferId;

    cmdData.vertexBufferIdsKey = IMPL.resourceDataProvider.vertexBufferIdsContainerStorage.store(
        {vertexBufferIds.data(), vertexBufferIds.size()});
    cmdData.vertexLayoutsKey = IMPL.resourceDataProvider.vertexLayoutsContainerStorage.store(
        {vertexLayouts.data(), vertexLayouts.size()});
    IMPL.resourceCommandBuffer << cmdData.type << cmdData;
    return cmdData.id;
}

Texture2DId ResourceCommandBuffer::createTexture2D(uint32_t width, uint32_t height,
                                                   TextureFormat format, const byte_t *pixels) {
    assert(pixels);
    CreateTexture2DCmdData cmdData;
    cmdData.id = _allocator.allocTexture2DId();
    cmdData.width = width;
    cmdData.height = height;
    cmdData.format = format;
    cmdData.dataKey = IMPL.resourceDataProvider.byteContainerStorage.store(
        ByteContainer(pixels, width * height * getTextureFormatInfo(format).blockSize));
    IMPL.resourceCommandBuffer << cmdData.type << cmdData;
    return cmdData.id;
}

Texture2DArrayId ResourceCommandBuffer::createTexture2DArray(uint32_t width, uint32_t height,
                                                             uint32_t count, TextureFormat format) {
    CreateTexture2DArrayCmdData cmdData;
    cmdData.id = _allocator.allocTexture2DArrayId();
    cmdData.width = width;
    cmdData.height = height;
    cmdData.count = count;
    cmdData.format = format;
    IMPL.resourceCommandBuffer << cmdData.type << cmdData;
    return cmdData.id;
}

VertexShaderId ResourceCommandBuffer::createVertexShader(const std::string &src,
                                                         ResultCallback callback) {
    CreateVertexShaderCmdData cmdData;
    cmdData.id = _allocator.allocVertexShaderId();
    cmdData.srcKey = IMPL.resourceDataProvider.stringContainerStorage.store(
        StringContainer(src.data(), src.length() + 1));
    IMPL.resourceCommandBuffer << cmdData.type << cmdData;
    if (callback) {
        getResultCallbackTable().add(hash(cmdData.id), callback);
    }
    return cmdData.id;
}

FragmentShaderId ResourceCommandBuffer::createFragmentShader(const std::string &src,
                                                             ResultCallback callback) {
    CreateFragmentShaderCmdData cmdData;
    cmdData.id = _allocator.allocFragmentShaderId();
    cmdData.srcKey = IMPL.resourceDataProvider.stringContainerStorage.store(
        StringContainer(src.data(), src.length() + 1));
    IMPL.resourceCommandBuffer << cmdData.type << cmdData;
    if (callback) {
        getResultCallbackTable().add(hash(cmdData.id), callback);
    }
    return cmdData.id;
}

ShaderProgramId ResourceCommandBuffer::createShaderProgram(VertexShaderId vertexShaderId,
                                                           FragmentShaderId fragmentShaderId,
                                                           ResultCallback callback) {
    CreateShaderProgramCmdData cmdData;
    cmdData.id = _allocator.allocShaderProgramId();
    cmdData.vertexShaderId = vertexShaderId;
    cmdData.fragmentShaderId = fragmentShaderId;
    IMPL.resourceCommandBuffer << cmdData.type << cmdData;
    if (callback) {
        getResultCallbackTable().add(hash(cmdData.id), callback);
    }
    return cmdData.id;
}

UniformId ResourceCommandBuffer::createUniform(const std::string &name, UniformType type) {
    CreateUniformCmdData cmdData;
    cmdData.id = _allocator.allocUniformId();
    cmdData.dataType = type;
    cmdData.nameKey = IMPL.resourceDataProvider.stringContainerStorage.store(
        StringContainer(name.data(), name.length() + 1));
    IMPL.resourceCommandBuffer << cmdData.type << cmdData;
    return cmdData.id;
}

UniformInt1Id ResourceCommandBuffer::createUniformInt1(const std::string &name) {
    assert(!name.empty());
    UniformId id = createUniform(name, UniformType::int1);
    return static_cast<UniformInt1Id>(id);
}

UniformInt2Id ResourceCommandBuffer::createUniformInt2(const std::string &name) {
    assert(!name.empty());
    UniformId id = createUniform(name, UniformType::int2);
    return static_cast<UniformInt2Id>(id);
}

UniformInt3Id ResourceCommandBuffer::createUniformInt3(const std::string &name) {
    assert(!name.empty());
    UniformId id = createUniform(name, UniformType::int3);
    return static_cast<UniformInt3Id>(id);
}

UniformInt4Id ResourceCommandBuffer::createUniformInt4(const std::string &name) {
    assert(!name.empty());
    UniformId id = createUniform(name, UniformType::int4);
    return static_cast<UniformInt4Id>(id);
}

UniformFloat1Id ResourceCommandBuffer::createUniformFloat1(const std::string &name) {
    assert(!name.empty());
    UniformId id = createUniform(name, UniformType::float1);
    return static_cast<UniformFloat1Id>(id);
}

UniformFloat2Id ResourceCommandBuffer::createUniformFloat2(const std::string &name) {
    assert(!name.empty());
    UniformId id = createUniform(name, UniformType::float2);
    return static_cast<UniformFloat2Id>(id);
}

UniformFloat3Id ResourceCommandBuffer::createUniformFloat3(const std::string &name) {
    assert(!name.empty());
    UniformId id = createUniform(name, UniformType::float3);
    return static_cast<UniformFloat3Id>(id);
}

UniformFloat4Id ResourceCommandBuffer::createUniformFloat4(const std::string &name) {
    assert(!name.empty());
    UniformId id = createUniform(name, UniformType::float4);
    return static_cast<UniformFloat4Id>(id);
}

UniformMat4Id ResourceCommandBuffer::createUniformMat4(const std::string &name) {
    UniformId id = createUniform(name, UniformType::mat4);
    assert(!name.empty());
    return static_cast<UniformMat4Id>(id);
}

UniformSampler2DId ResourceCommandBuffer::createUniformSampler2D(const std::string &name) {
    assert(!name.empty());
    UniformId id = createUniform(name, UniformType::sampler2D);
    return static_cast<UniformSampler2DId>(id);
}

void ResourceCommandBuffer::setSubData(DynamicIndexBufferId dynamicIndexBufferId,
                                       const index_t *data, size_t size, size_t offset) {
    assert(data);
    SetIndexBufferSubDataCmdData cmdData;
    cmdData.id = dynamicIndexBufferId;
    cmdData.offset = offset;
    cmdData.dataKey =
        IMPL.resourceDataProvider.indexBufferDataContainerStorage.store(IndexContainer(data, size));
    IMPL.resourceCommandBuffer << cmdData.type << cmdData;
}

void ResourceCommandBuffer::setSubData(DynamicVertexBufferId dynamicVertexBufferId,
                                       const vertex_t *data, size_t size, size_t offset) {
    assert(data);
    SetVertexBufferSubDataCmdData cmdData;
    cmdData.id = dynamicVertexBufferId;
    cmdData.offset = offset;
    cmdData.dataKey = IMPL.resourceDataProvider.vertexBufferDataContainerStorage.store(
        VertexContainer(data, size));
    IMPL.resourceCommandBuffer << cmdData.type << cmdData;
}

void ResourceCommandBuffer::setSubData(ShaderBufferId shaderBufferId, const byte_t *data,
                                       size_t size, size_t offset) {
    assert(data);
    SetShaderBufferSubDataCmdData cmdData;
    cmdData.id = shaderBufferId;
    cmdData.offset = offset;
    cmdData.dataKey =
        IMPL.resourceDataProvider.byteContainerStorage.store(ByteContainer(data, size));
    IMPL.resourceCommandBuffer << cmdData.type << cmdData;
}

void ResourceCommandBuffer::setSubData(Texture2DId texture2DId, uint32_t width, uint32_t height,
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
    cmdData.dataKey = IMPL.resourceDataProvider.byteContainerStorage.store(
        ByteContainer(pixels, width * height * getTextureFormatInfo(textureFormat).blockSize));
    IMPL.resourceCommandBuffer << cmdData.type << cmdData;
}

void ResourceCommandBuffer::setSubData(Texture2DArrayId texture2DArrayId, uint32_t index,
                                       uint32_t width, uint32_t height, TextureFormat textureFormat,
                                       const byte_t *pixels, uint32_t widthOffset,
                                       uint32_t heightOffset) {
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
    cmdData.dataKey = IMPL.resourceDataProvider.byteContainerStorage.store(
        ByteContainer(pixels, width * height * getTextureFormatInfo(textureFormat).blockSize));
    IMPL.resourceCommandBuffer << cmdData.type << cmdData;
}

void ResourceCommandBuffer::destroy(IndexBufferId indexBufferId) {
    if (_allocator.isValid(indexBufferId)) {
        return;
    }
    DestroyIndexBufferCmdData cmdData;
    cmdData.id = indexBufferId;
    IMPL.resourceCommandBuffer << cmdData.type << cmdData;
}

void ResourceCommandBuffer::destroy(VertexBufferId vertexBufferId) {
    if (_allocator.isValid(vertexBufferId)) {
        return;
    }
    DestroyVertexBufferCmdData cmdData;
    cmdData.id = vertexBufferId;
    IMPL.resourceCommandBuffer << cmdData.type << cmdData;
}

void ResourceCommandBuffer::destroy(UniformBufferId uniformBufferId) {
    if (_allocator.isValid(uniformBufferId)) {
        return;
    }
    DestroyUniformBufferCmdData cmdData;
    cmdData.id = uniformBufferId;
    IMPL.resourceCommandBuffer << cmdData.type << cmdData;
}

void ResourceCommandBuffer::destroy(ShaderBufferId shaderBufferId) {
    if (_allocator.isValid(shaderBufferId)) {
        return;
    }
    DestroyShaderBufferCmdData cmdData;
    cmdData.id = shaderBufferId;
    IMPL.resourceCommandBuffer << cmdData.type << cmdData;
}

void ResourceCommandBuffer::destroy(VertexAssemblyId vertexAssemblyId) {
    if (_allocator.isValid(vertexAssemblyId)) {
        return;
    }
    DestroyVertexAssemblyCmdData cmdData;
    cmdData.id = vertexAssemblyId;
    IMPL.resourceCommandBuffer << cmdData.type << cmdData;
}

void ResourceCommandBuffer::destroy(Texture2DId texture2DId) {
    if (_allocator.isValid(texture2DId)) {
        return;
    }
    DestroyTexture2DCmdData cmdData;
    cmdData.id = texture2DId;
    IMPL.resourceCommandBuffer << cmdData.type << cmdData;
}

void ResourceCommandBuffer::destroy(Texture2DArrayId vertexShaderId) {
    if (_allocator.isValid(vertexShaderId)) {
        return;
    }
    DestroyTexture2DArrayCmdData cmdData;
    cmdData.id = vertexShaderId;
    IMPL.resourceCommandBuffer << cmdData.type << cmdData;
}

void ResourceCommandBuffer::destroy(VertexShaderId vertexShaderId) {
    if (_allocator.isValid(vertexShaderId)) {
        return;
    }
    DestroyVertexShaderCmdData cmdData;
    cmdData.id = vertexShaderId;
    IMPL.resourceCommandBuffer << cmdData.type << cmdData;
}

void ResourceCommandBuffer::destroy(FragmentShaderId fragmentShaderId) {
    if (_allocator.isValid(fragmentShaderId)) {
        return;
    }
    DestroyFragmentShaderCmdData cmdData;
    cmdData.id = fragmentShaderId;
    IMPL.resourceCommandBuffer << cmdData.type << cmdData;
}

void ResourceCommandBuffer::destroy(ShaderProgramId shaderProgramId) {
    if (_allocator.isValid(shaderProgramId)) {
        return;
    }
    DestroyShaderProgramCmdData cmdData;
    cmdData.id = shaderProgramId;
    IMPL.resourceCommandBuffer << cmdData.type << cmdData;
}

void ResourceCommandBuffer::destroy(UniformId uniformId) {
    if (!_allocator.free(uniformId)) {
        // TODO: Warning
        return;
    }
}

IndexBufferIdGuard ResourceCommandBuffer::createIndexBufferGuard(const index_t *data, size_t size) {
    return IndexBufferIdGuard(_instanceId, createIndexBuffer(data, size));
}

IndexBufferIdGuard ResourceCommandBuffer::createIndexBufferGuard(const IndexContainer &data) {
    return IndexBufferIdGuard(_instanceId, createIndexBuffer(data));
}

DynIndexBufferIdGuard ResourceCommandBuffer::createDynamicIndexBufferGuard(size_t size) {
    return DynIndexBufferIdGuard(_instanceId, createDynamicIndexBuffer(size));
}

VertexBufferIdGuard ResourceCommandBuffer::createVertexBufferGuard(const vertex_t *data,
                                                                   size_t size) {
    return VertexBufferIdGuard(_instanceId, createVertexBuffer(data, size));
}

VertexBufferIdGuard ResourceCommandBuffer::createVertexBufferGuard(const VertexContainer &data) {
    return VertexBufferIdGuard(_instanceId, createVertexBuffer(data));
}

DynVertexBufferIdGuard ResourceCommandBuffer::createDynamicVertexBufferGuard(size_t size) {
    return DynVertexBufferIdGuard(_instanceId, createDynamicVertexBuffer(size));
}

UniformBufferIdGuard ResourceCommandBuffer::createUniformBufferGuard(const byte_t *data,
                                                                     size_t size) {
    return UniformBufferIdGuard(_instanceId, createUniformBuffer(data, size));
}

UniformBufferIdGuard ResourceCommandBuffer::createUniformBufferGuard(const ByteContainer &data) {
    return UniformBufferIdGuard(_instanceId, createUniformBuffer(data));
}

ShaderBufferIdGuard ResourceCommandBuffer::createShaderBufferGuard(const byte_t *data,
                                                                   size_t size) {
    return ShaderBufferIdGuard(_instanceId, createShaderBuffer(data, size));
}

ShaderBufferIdGuard ResourceCommandBuffer::createShaderBufferGuard(const ByteContainer &data) {
    return ShaderBufferIdGuard(_instanceId, createShaderBuffer(data));
}

ShaderBufferIdGuard ResourceCommandBuffer::createShaderBufferGuard(size_t size) {
    return ShaderBufferIdGuard(_instanceId, createShaderBuffer(size));
}

VertexAssemblyIdGuard
ResourceCommandBuffer::createVertexAssemblyGuard(IndexBufferId indexBufferId,
                                                 const std::vector<VertexBufferId> &vertexBufferIds,
                                                 const std::vector<VertexLayout> &vertexLayouts) {
    return VertexAssemblyIdGuard(
        _instanceId, createVertexAssembly(indexBufferId, vertexBufferIds, vertexLayouts));
}

Texture2DIdGuard ResourceCommandBuffer::createTexture2DGuard(uint32_t width, uint32_t height,
                                                             TextureFormat format,
                                                             const byte_t *pixels) {
    return Texture2DIdGuard(_instanceId, createTexture2D(width, height, format, pixels));
}

Texture2DArrayIdGuard ResourceCommandBuffer::createTexture2DArrayGuard(uint32_t width,
                                                                       uint32_t height,
                                                                       uint32_t count,
                                                                       TextureFormat format) {
    return Texture2DArrayIdGuard(_instanceId, createTexture2DArray(width, height, count, format));
}

VertexShaderIdGuard ResourceCommandBuffer::createVertexShaderGuard(const std::string &src,
                                                                   ResultCallback callback) {
    return VertexShaderIdGuard(_instanceId, createVertexShader(src, callback));
}

FragmentShaderIdGuard ResourceCommandBuffer::createFragmentShaderGuard(const std::string &src,
                                                                       ResultCallback callback) {
    return FragmentShaderIdGuard(_instanceId, createFragmentShader(src, callback));
}

ShaderProgramIdGuard ResourceCommandBuffer::createShaderProgramGuard(
    VertexShaderId vertexShaderId, FragmentShaderId fragmentShaderId, ResultCallback callback) {
    return ShaderProgramIdGuard(_instanceId,
                                createShaderProgram(vertexShaderId, fragmentShaderId, callback));
}

void ResourceCommandBuffer::reset() {
    IMPL.reset();
}

bool ResourceCommandBuffer::isEmpty() const {
    return IMPL.resourceCommandBuffer.isEmpty();
}
} // namespace rendell
