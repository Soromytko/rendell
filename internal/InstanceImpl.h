#pragma once
#include <rendell/RenderCommandBuffer.h>
#include <rendell/ResourceCommandBuffer.h>

#include <CommandBufferPool.h>
#include <RenderPipelineStorage.h>
#include <ResourceIdsAllocator.h>

#include <cassert>
#include <memory>

namespace rendell {
class GarbageCollector;
class ReleasedResourceIds;

struct InstanceImpl {
    friend class Instance;

private:
    struct SwappedResourceCommandBuffers {
        explicit SwappedResourceCommandBuffers(InstanceId id, ResourceIdAllocator &allocator)
            : _buffer0(id, allocator)
            , _buffer1(id, allocator)
            , _currentBuffer(&_buffer0) {}

        SwappedResourceCommandBuffers(const SwappedResourceCommandBuffers &) = delete;
        SwappedResourceCommandBuffers(SwappedResourceCommandBuffers &&) = delete;
        SwappedResourceCommandBuffers &operator=(const SwappedResourceCommandBuffers &) = delete;
        SwappedResourceCommandBuffers &operator=(SwappedResourceCommandBuffers &&) = delete;

        ResourceCommandBuffer *operator->() {
            assert(_currentBuffer);
            return _currentBuffer;
        }

        ResourceCommandBuffer &operator*() {
            assert(_currentBuffer);
            return *_currentBuffer;
        }

        inline ResourceCommandBuffer *swap() noexcept {
            assert(_currentBuffer);
            auto prev = _currentBuffer;
            _currentBuffer = _currentBuffer == &_buffer0 ? &_buffer1 : &_buffer0;
            _currentBuffer->reset();
            return prev;
        }

    private:
        ResourceCommandBuffer _buffer0;
        ResourceCommandBuffer _buffer1;
        ResourceCommandBuffer *_currentBuffer;
    };

    InstanceId id;
    Initer initer;
    ResourceIdAllocator resourceIdAllocator;
    CommandBufferPool<ResourceCommandBuffer> resourceCommandBufferPool;
    CommandBufferPool<RenderCommandBuffer> renderCommandBufferPool;
    SwappedResourceCommandBuffers defferedResourceCommandBuffers;
    RenderPipelineStorage renderPipelineStorage;

    RenderPipeline &getRenderPipeline(NativeViewId nativeViewId);

    InstanceImpl(InstanceId id, Initer initer)
        : id(id)
        , initer(initer)
        , resourceIdAllocator(initer.maxResourceIdCount)
        , resourceCommandBufferPool([&resourceIdAllocator = resourceIdAllocator, id, &initer]() {
            std::vector<std::unique_ptr<ResourceCommandBuffer>> result{};
            for (size_t i = 0; i < initer.maxResourceCommandBufferPerFrame; i++) {
                result.push_back(std::make_unique<ResourceCommandBuffer>(id, resourceIdAllocator));
            }
            return result;
        }())
        , renderCommandBufferPool([&resourceIdAllocator = resourceIdAllocator, &initer]() {
            std::vector<std::unique_ptr<RenderCommandBuffer>> result{};
            for (size_t i = 0; i < initer.maxRenderCommandBufferPerFrame; i++) {
                result.push_back(std::make_unique<RenderCommandBuffer>());
            }
            return result;
        }())
        , defferedResourceCommandBuffers(id, resourceIdAllocator)
        , renderPipelineStorage(
              [&pool = resourceCommandBufferPool](ResourceCommandBuffer *buffer) {
                  assert(buffer);
                  pool.push(buffer);
              },
              [&pool = renderCommandBufferPool](RenderCommandBuffer *buffer) {
                  assert(buffer);
                  pool.push(buffer);
              }) {}

    void submitCommandBuffer(ResourceCommandBuffer *buffer, NativeViewId nativeViewId);
    void submitCommandBuffer(RenderCommandBuffer *buffer, NativeViewId nativeViewId);

    void submitGarbageCollector(NativeViewId nativeViewId, GarbageCollector &gc);

    void releaseResourceIds(const ReleasedResourceIds &ids);
};
} // namespace rendell
