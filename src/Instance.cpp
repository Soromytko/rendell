#include <rendell/Instance.h>

#include <InstanceImpl.h>
#include <InstanceRegistry.h>
#include <Pool.h>
#include <RenderPipeline.h>
#include <RenderPipelineStorage.h>
#include <logging.h>

#define IMPL getImpl(_implStorage)

namespace rendell {
static InstanceImpl &getImpl(std::byte *storage) {
    return *reinterpret_cast<InstanceImpl *>(storage);
}

void Instance::CommandBufferWrapper<ResourceCommandBuffer>::end() noexcept {
    assert(_buffer);
    getImpl(_instance._implStorage).submitCommandBuffer(_buffer, _nativeViewId);
}

void Instance::CommandBufferWrapper<RenderCommandBuffer>::end() noexcept {
    assert(_buffer);
    getImpl(_instance._implStorage).submitCommandBuffer(_buffer, _nativeViewId);
}

Instance::Instance(Initer initer)
    : _id(InstanceRegistry::getInstance().getRegistry().registerEntry(this))
    , _garbageCollector(initer.garbageCollectorLockFreeCapacity) {
    static_assert(sizeof(InstanceImpl) == _implSize, "ImplSize is too small!");
    static_assert(alignof(InstanceImpl) == _implAlign, "ImplAlign mismatch!");

    if (!_id) {
        throw std::runtime_error("Failed to register Instance: Registry is full.");
    }

    new (_implStorage) InstanceImpl(_id, initer);
}

Instance::~Instance() {
    InstanceRegistry::getInstance().getRegistry().unregisterEntry(_id);

    IMPL.~InstanceImpl();
}

NativeViewId Instance::registerNativeView(NativeView nativeView) {
    InstanceImpl &impl = IMPL;
    const NativeViewId nativeViewId = impl.renderPipelineStorage.createRenderPipeline(
        impl.initer.api, nativeView, impl.initer.useSeparateRenderThread);
    if (nativeViewId == InvalidNativeViewId) {
        RENDELL_WARNING("Failure to register native view!");
    }
    return nativeViewId;
}

void Instance::unregisterNativeView(NativeViewId nativeViewId) {
    if (nativeViewId == InvalidNativeViewId) {
        return;
    }
    if (!IMPL.renderPipelineStorage.releaseRenderPipeline(nativeViewId)) {
        RENDELL_WARNING("This is not valid NativeViewId: {}", static_cast<size_t>(nativeViewId));
        return;
    }
}

Instance::ResourceCommandBufferScoped Instance::beginResourceScope(NativeViewId nativeViewId) {
    auto buffer = IMPL.resourceCommandBufferPool.pop();
    return ResourceCommandBufferScoped(*this, buffer, nativeViewId);
}

Instance::RenderCommandBufferScoped Instance::beginRenderScope(NativeViewId nativeViewId) {
    auto buffer = IMPL.renderCommandBufferPool.pop();
    return RenderCommandBufferScoped(*this, buffer, nativeViewId);
}

void Instance::endRenderScope(ResourceCommandBufferScoped wrapper) {
    assert(wrapper._buffer);
    assert(this == &wrapper._instance);
}

void Instance::endRenderScope(RenderCommandBufferScoped wrapper) {
    assert(wrapper._buffer);
    assert(this == &wrapper._instance);
}

void Instance::renderFrame(NativeViewId nativeViewId) {
    IMPL.submitGarbageCollector(nativeViewId, _garbageCollector);
    auto &renderPipeline = IMPL.getRenderPipeline(nativeViewId);
    renderPipeline.waitAndRender();

    auto &releasedResourceIds = renderPipeline.getReleasedResourceIds();
    IMPL.releaseResourceIds(releasedResourceIds);
}

bool Instance::isValid(IndexBufferId id) {
    return IMPL.resourceIdAllocator.isValid(id);
}

bool Instance::isValid(VertexBufferId id) {
    return IMPL.resourceIdAllocator.isValid(id);
}

bool Instance::isValid(UniformBufferId id) {
    return IMPL.resourceIdAllocator.isValid(id);
}

bool Instance::isValid(ShaderBufferId id) {
    return IMPL.resourceIdAllocator.isValid(id);
}

bool Instance::isValid(VertexAssemblyId id) {
    return IMPL.resourceIdAllocator.isValid(id);
}

bool Instance::isValid(Texture2DId id) {
    return IMPL.resourceIdAllocator.isValid(id);
}

bool Instance::isValid(Texture2DArrayId id) {
    return IMPL.resourceIdAllocator.isValid(id);
}

bool Instance::isValid(VertexShaderId id) {
    return IMPL.resourceIdAllocator.isValid(id);
}

bool Instance::isValid(FragmentShaderId id) {
    return IMPL.resourceIdAllocator.isValid(id);
}

bool Instance::isValid(ShaderProgramId id) {
    return IMPL.resourceIdAllocator.isValid(id);
}

bool Instance::isValid(UniformId id) {
    return IMPL.resourceIdAllocator.isValid(id);
}

} // namespace rendell
