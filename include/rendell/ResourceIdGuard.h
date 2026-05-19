#pragma once
#include <rendell/DataType.h>
#include <rendell/GarbageCollector.h>
#include <rendell/ResourceId.h>
#include <rendell/Service.h>

#include <concepts>

namespace rendell {
template <typename TResourceId>
    requires std::derived_from<TResourceId, ResourceId>
class ResourceIdGuard {
public:
    ResourceIdGuard()
        : _instanceId(InvalidInstanceId)
        , _id({}) {}

    ResourceIdGuard(InstanceId instanceId, TResourceId id)
        : _instanceId(instanceId)
        , _id(id) {}

    ResourceIdGuard(ResourceIdGuard &&other) noexcept
        : _instanceId(other._instanceId)
        , _id(other._id) {
        other._id = {};
    }

    ResourceIdGuard &operator=(ResourceIdGuard &&other) noexcept {
        if (this != &other) {
            if (_id.isValid()) {
                free();
            }
            _instanceId = other._instanceId;
            _id = other._id;
            other._id = {};
        }
        return *this;
    }

    ResourceIdGuard(const ResourceIdGuard &) = delete;
    ResourceIdGuard &operator=(const ResourceIdGuard &) = delete;

    ~ResourceIdGuard() noexcept { reset(); }

    inline void reset(TResourceId id = {}, InstanceId instanceId = {}) noexcept {
        if (_id.isValid()) {
            free();
            _id = {};
            _instanceId = instanceId;
        }
    }

    inline TResourceId getId() const noexcept { return _id; }

    inline bool isValid() const noexcept { return _id.isValid(); }

    explicit operator bool() const { return _id.isValid(); }

private:
    void free() noexcept {
        assert(_id.isValid());
        GarbageCollector *gc = nullptr;
        if (auto lock = beginUsingGC(_instanceId, gc)) {
            gc->enqueueDestroy(_id);
        }
    }

    InstanceId _instanceId;
    TResourceId _id;
};

using IndexBufferIdGuard = ResourceIdGuard<IndexBufferId>;
using DynIndexBufferIdGuard = ResourceIdGuard<DynamicIndexBufferId>;
using VertexBufferIdGuard = ResourceIdGuard<VertexBufferId>;
using DynVertexBufferIdGuard = ResourceIdGuard<DynamicVertexBufferId>;
using VertexAssemblyIdGuard = ResourceIdGuard<VertexAssemblyId>;
using ShaderBufferIdGuard = ResourceIdGuard<ShaderBufferId>;
using UniformBufferIdGuard = ResourceIdGuard<UniformBufferId>;
using Texture2DIdGuard = ResourceIdGuard<Texture2DId>;
using Texture2DArrayIdGuard = ResourceIdGuard<Texture2DArrayId>;
using VertexShaderIdGuard = ResourceIdGuard<VertexShaderId>;
using FragmentShaderIdGuard = ResourceIdGuard<FragmentShaderId>;
using ShaderProgramIdGuard = ResourceIdGuard<ShaderProgramId>;
using UniformInt1IdGuard = ResourceIdGuard<UniformInt1Id>;
using UniformInt2IdGuard = ResourceIdGuard<UniformInt2Id>;
using UniformInt3IdGuard = ResourceIdGuard<UniformInt3Id>;
using UniformInt4IdGuard = ResourceIdGuard<UniformInt4Id>;
using UniformFloat1IdGuard = ResourceIdGuard<UniformFloat1Id>;
using UniformFloat2IdGuard = ResourceIdGuard<UniformFloat2Id>;
using UniformFloat3IdGuard = ResourceIdGuard<UniformFloat3Id>;
using UniformFloat4IdGuard = ResourceIdGuard<UniformFloat4Id>;
using UniformMat4IdGuard = ResourceIdGuard<UniformMat4Id>;
using UniformSampler2DIdGuard = ResourceIdGuard<UniformSampler2DId>;

} // namespace rendell