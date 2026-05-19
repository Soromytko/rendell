#include <InstanceImpl.h>

#include <ReleasedResourceIds.h>
#include <RenderPipeline.h>
#include <rendell/GarbageCollector.h>

#include <cassert>

namespace rendell {
RenderPipeline &InstanceImpl::getRenderPipeline(NativeViewId nativeViewId) {
    assert(nativeViewId != InvalidNativeViewId);
    RenderPipeline *renderPipeline = renderPipelineStorage.getRenderPipeline(nativeViewId);
    assert(renderPipeline);
    return *renderPipeline;
}

void InstanceImpl::submitCommandBuffer(ResourceCommandBuffer *buffer, NativeViewId nativeViewId) {
    assert(buffer);
    assert(nativeViewId != InvalidNativeViewId);
    getRenderPipeline(nativeViewId).submitResourceContext(buffer);
}

void InstanceImpl::submitCommandBuffer(RenderCommandBuffer *buffer, NativeViewId nativeViewId) {
    assert(buffer);
    assert(nativeViewId != InvalidNativeViewId);
    getRenderPipeline(nativeViewId).submitRenderContext(buffer);
}

void InstanceImpl::submitGarbageCollector(NativeViewId nativeViewId, GarbageCollector &gc) {
    auto &current = *defferedResourceCommandBuffers;
    gc.collect(current);
    if (!current.isEmpty()) {
        submitCommandBuffer(defferedResourceCommandBuffers.swap(), nativeViewId);
    }
}

void InstanceImpl::releaseResourceIds(const ReleasedResourceIds &ids) {
    for (auto id : ids.indexBufferIds) {
        resourceIdAllocator.free(id);
    }
    for (auto id : ids.vertexBufferIds) {
        resourceIdAllocator.free(id);
    }
    for (auto id : ids.vertexAssemblyIds) {
        resourceIdAllocator.free(id);
    }
    for (auto id : ids.shaderBufferIds) {
        resourceIdAllocator.free(id);
    }
    for (auto id : ids.texture2DIds) {
        resourceIdAllocator.free(id);
    }
    for (auto id : ids.texture2DArrayIds) {
        resourceIdAllocator.free(id);
    }
    for (auto id : ids.uniformBufferIds) {
        resourceIdAllocator.free(id);
    }
    for (auto id : ids.vertexShaderIds) {
        resourceIdAllocator.free(id);
    }
    for (auto id : ids.fragmentShaderIds) {
        resourceIdAllocator.free(id);
    }
    for (auto id : ids.shaderProgramIds) {
        resourceIdAllocator.free(id);
    }
    for (auto id : ids.uniformIds) {
        resourceIdAllocator.free(id);
    }
}
} // namespace rendell