#pragma once
#include <rendell/DataType.h>
#include <rendell/GarbageCollector.h>
#include <rendell/RenderCommandBuffer.h>
#include <rendell/ResourceCommandBuffer.h>
#include <rendell/ResourceId.h>
#include <rendell/init_types.h>

#include <cassert>
#include <concepts>
#include <memory>
#include <utility>

namespace rendell {
class Instance final {
public:
    template <typename TCommandBuffer>
        requires std::same_as<TCommandBuffer, ResourceCommandBuffer> ||
                 std::same_as<TCommandBuffer, RenderCommandBuffer>
    class CommandBufferWrapper final {
        friend Instance;

    private:
        CommandBufferWrapper(Instance &instance, TCommandBuffer *buffer, NativeViewId nativeViewId)
            : _instance(instance)
            , _buffer(buffer)
            , _nativeViewId(nativeViewId) {
            assert(_buffer);
        }

    public:
        CommandBufferWrapper(const CommandBufferWrapper &) = delete;
        CommandBufferWrapper &operator=(const CommandBufferWrapper &) = delete;

        CommandBufferWrapper(CommandBufferWrapper &&other) noexcept
            : _instance(other._instance)
            , _buffer(other._buffer)
            , _nativeViewId(other._nativeViewId) {
            other._buffer = nullptr;
            other._nativeViewId = InvalidNativeViewId;
        }

        CommandBufferWrapper &operator=(CommandBufferWrapper &&other) noexcept {
            if (this != &other) {
                assert(&_instance == &other._instance);
                if (_buffer) {
                    end();
                }
                _buffer = std::exchange(other._buffer, nullptr);
                _nativeViewId = std::exchange(other._nativeViewId, InvalidNativeViewId);
            }
            return *this;
        }

        ~CommandBufferWrapper() noexcept {
            if (_buffer) {
                end();
            }
        }

        bool isValid() const noexcept { return _buffer != nullptr; }

        TCommandBuffer *operator->() noexcept {
            assert(_buffer);
            return _buffer;
        }

        TCommandBuffer &operator*() noexcept {
            assert(_buffer);
            return *_buffer;
        }

        TCommandBuffer &get() noexcept {
            assert(_buffer);
            return *_buffer;
        }

    private:
        void end() noexcept;

        Instance &_instance;
        TCommandBuffer *_buffer;
        NativeViewId _nativeViewId;
    };

    using ResourceCommandBufferScoped = CommandBufferWrapper<ResourceCommandBuffer>;
    using RenderCommandBufferScoped = CommandBufferWrapper<RenderCommandBuffer>;

    Instance(Initer initer);
    ~Instance();

    Instance(const Instance &) = delete;
    Instance(Instance &&) = delete;
    Instance &operator=(const Instance &) = delete;
    Instance &operator=(Instance &&) = delete;

    InstanceId getId() const { return _id; }

    GarbageCollector &getGarbageCollector() { return _garbageCollector; }

    NativeViewId registerNativeView(NativeView nativeViewId);
    void unregisterNativeView(NativeViewId nativeViewId);

    ResourceCommandBufferScoped beginResourceScope(NativeViewId nativeViewId);
    RenderCommandBufferScoped beginRenderScope(NativeViewId nativeViewId);

    void endRenderScope(ResourceCommandBufferScoped wrapper);
    void endRenderScope(RenderCommandBufferScoped wrapper);

    void renderFrame(NativeViewId nativeViewId);

    bool isValid(IndexBufferId id);
    bool isValid(VertexBufferId id);
    bool isValid(UniformBufferId id);
    bool isValid(ShaderBufferId id);
    bool isValid(VertexAssemblyId id);
    bool isValid(Texture2DId id);
    bool isValid(Texture2DArrayId id);
    bool isValid(VertexShaderId id);
    bool isValid(FragmentShaderId id);
    bool isValid(ShaderProgramId id);
    bool isValid(UniformId id);

private:
    const InstanceId _id;
    GarbageCollector _garbageCollector;

    static constexpr size_t _implSize = 6208;
    static constexpr size_t _implAlign = 64;
    alignas(_implAlign) std::byte _implStorage[_implSize];
};
} // namespace rendell
