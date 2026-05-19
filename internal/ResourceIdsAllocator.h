#pragma once
#include <ResourceIdStorage.h>
#include <rendell/ResourceId.h>

namespace rendell {
class ResourceIdAllocator {
private:
    ResourceIdStorage<IndexBufferId> _indexBufferIdStorage;
    ResourceIdStorage<VertexBufferId> _vertexBufferIdStorage;
    ResourceIdStorage<UniformBufferId> _uniformBufferIdStorage;
    ResourceIdStorage<ShaderBufferId> _shaderBufferIdStorage;
    ResourceIdStorage<VertexAssemblyId> _vertexAssemblyIdStorage;
    ResourceIdStorage<Texture2DId> _texture2DIdStorage;
    ResourceIdStorage<Texture2DArrayId> _texture2DArrayIdStorage;
    ResourceIdStorage<VertexShaderId> _vertexShaderIdStorage;
    ResourceIdStorage<FragmentShaderId> _fragmentShaderIdStorage;
    ResourceIdStorage<ShaderProgramId> _shaderProgramIdStorage;
    ResourceIdStorage<UniformId> _uniformIdStorage;

public:
    ResourceIdAllocator(uint16_t capacity)
        : _indexBufferIdStorage{capacity}
        , _vertexBufferIdStorage{capacity}
        , _uniformBufferIdStorage{capacity}
        , _shaderBufferIdStorage{capacity}
        , _vertexAssemblyIdStorage{capacity}
        , _texture2DIdStorage{capacity}
        , _texture2DArrayIdStorage{capacity}
        , _vertexShaderIdStorage{capacity}
        , _fragmentShaderIdStorage{capacity}
        , _shaderProgramIdStorage{capacity}
        , _uniformIdStorage{capacity} {}

    // Validation
    inline bool isValid(IndexBufferId id) const { return _indexBufferIdStorage.isValid(id); }

    inline bool isValid(VertexBufferId id) const { return _vertexBufferIdStorage.isValid(id); }

    inline bool isValid(UniformBufferId id) const { return _uniformBufferIdStorage.isValid(id); }

    inline bool isValid(ShaderBufferId id) const { return _shaderBufferIdStorage.isValid(id); }

    inline bool isValid(VertexAssemblyId id) const { return _vertexAssemblyIdStorage.isValid(id); }

    inline bool isValid(Texture2DId id) const { return _texture2DIdStorage.isValid(id); }

    inline bool isValid(Texture2DArrayId id) const { return _texture2DArrayIdStorage.isValid(id); }

    inline bool isValid(VertexShaderId id) const { return _vertexShaderIdStorage.isValid(id); }

    inline bool isValid(FragmentShaderId id) const { return _fragmentShaderIdStorage.isValid(id); }

    inline bool isValid(ShaderProgramId id) const { return _shaderProgramIdStorage.isValid(id); }

    inline bool isValid(UniformId id) const { return _uniformIdStorage.isValid(id); }

    // Allocation
    inline auto allocIndexBufferId() { return _indexBufferIdStorage.alloc(); }

    inline auto allocVertexBufferId() { return _vertexBufferIdStorage.alloc(); }

    inline auto allocUniformBufferId() { return _uniformBufferIdStorage.alloc(); }

    inline auto allocShaderBufferId() { return _shaderBufferIdStorage.alloc(); }

    inline auto allocVertexAssemblyId() { return _vertexAssemblyIdStorage.alloc(); }

    inline auto allocTexture2DId() { return _texture2DIdStorage.alloc(); }

    inline auto allocTexture2DArrayId() { return _texture2DArrayIdStorage.alloc(); }

    inline auto allocVertexShaderId() { return _vertexShaderIdStorage.alloc(); }

    inline auto allocFragmentShaderId() { return _fragmentShaderIdStorage.alloc(); }

    inline auto allocShaderProgramId() { return _shaderProgramIdStorage.alloc(); }

    inline auto allocUniformId() { return _uniformIdStorage.alloc(); }

    // Deallocation
    inline bool free(IndexBufferId id) { return _indexBufferIdStorage.free(id); };

    inline bool free(VertexBufferId id) { return _vertexBufferIdStorage.free(id); }

    inline bool free(UniformBufferId id) { return _uniformBufferIdStorage.free(id); }

    inline bool free(ShaderBufferId id) { return _shaderBufferIdStorage.free(id); }

    inline bool free(VertexAssemblyId id) { return _vertexAssemblyIdStorage.free(id); }

    inline bool free(Texture2DId id) { return _texture2DIdStorage.free(id); }

    inline bool free(Texture2DArrayId id) { return _texture2DArrayIdStorage.free(id); }

    inline bool free(VertexShaderId id) { return _vertexShaderIdStorage.free(id); }

    inline bool free(FragmentShaderId id) { return _fragmentShaderIdStorage.free(id); }

    inline bool free(ShaderProgramId id) { return _shaderProgramIdStorage.free(id); }

    inline bool free(UniformId id) { return _uniformIdStorage.free(id); }
};
} // namespace rendell