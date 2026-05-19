#include <rendell/GarbageCollector.h>

#include <rendell/ResourceCommandBuffer.h>
#include <utils/MPMC_Queue.h>

#include <mutex>
#include <vector>

#define IMPL (*reinterpret_cast<Impl *>(_implStorage))

namespace rendell {
struct Impl {
    template <typename TResourceId> struct Queue {
        MPMC_Queue<TResourceId> queue;
        std::vector<TResourceId> vector;
        std::mutex mutex;

        void enqueue(TResourceId id) {
            if (!queue.enqueue(id)) {
                std::lock_guard<std::mutex> lock(mutex);
                vector.push_back(id);
            }
        }

        void collectAll(ResourceCommandBuffer &buffer) {
            TResourceId id;
            while (queue.dequeue(id)) {
                buffer.destroy(id);
            }
            std::lock_guard<std::mutex> lock(mutex);
            for (auto id : vector) {
                buffer.destroy(id);
            }
            vector.clear();
        }
    };

    Queue<IndexBufferId> indexBufferIdQueue;
    Queue<VertexBufferId> vertexBufferIdQueue;
    Queue<VertexAssemblyId> vertexAssemblyIdQueue;
    Queue<ShaderBufferId> shaderBufferIdQueue;
    Queue<Texture2DId> texture2DIdQueue;
    Queue<Texture2DArrayId> texture2DArrayIdQueue;
    Queue<UniformBufferId> uniformBufferIdQueue;
    Queue<VertexShaderId> vertexShaderIdQueue;
    Queue<FragmentShaderId> fragmentShaderIdQueue;
    Queue<ShaderProgramId> shaderProgramIdQueue;
    Queue<UniformId> uniformIdQueue;

    explicit Impl(size_t bufferCapacity)
        : indexBufferIdQueue(bufferCapacity)
        , vertexBufferIdQueue(bufferCapacity)
        , vertexAssemblyIdQueue(bufferCapacity)
        , shaderBufferIdQueue(bufferCapacity)
        , texture2DIdQueue(bufferCapacity)
        , texture2DArrayIdQueue(bufferCapacity)
        , uniformBufferIdQueue(bufferCapacity)
        , vertexShaderIdQueue(bufferCapacity)
        , fragmentShaderIdQueue(bufferCapacity)
        , shaderProgramIdQueue(bufferCapacity)
        , uniformIdQueue(bufferCapacity) {}

    void collect(ResourceCommandBuffer &buffer) {
        std::lock_guard<std::mutex> lock(collectMutex);

        indexBufferIdQueue.collectAll(buffer);
        vertexBufferIdQueue.collectAll(buffer);
        vertexAssemblyIdQueue.collectAll(buffer);
        shaderBufferIdQueue.collectAll(buffer);
        texture2DIdQueue.collectAll(buffer);
        texture2DArrayIdQueue.collectAll(buffer);
        uniformBufferIdQueue.collectAll(buffer);
        vertexShaderIdQueue.collectAll(buffer);
        fragmentShaderIdQueue.collectAll(buffer);
        shaderProgramIdQueue.collectAll(buffer);
        uniformIdQueue.collectAll(buffer);
    }

    std::mutex collectMutex;
};

GarbageCollector::GarbageCollector(size_t lockFreeCapacity) {
    static_assert(sizeof(Impl) == _implSize, "ImplSize is too small!");
    static_assert(alignof(Impl) == _implAlign, "ImplAlign mismatch!");

    new (_implStorage) Impl(lockFreeCapacity);
}

void GarbageCollector::collect(ResourceCommandBuffer &buffer) {
    IMPL.collect(buffer);
}

void GarbageCollector::enqueueDestroy(IndexBufferId id) {
    IMPL.indexBufferIdQueue.enqueue(id);
}

void GarbageCollector::enqueueDestroy(VertexBufferId id) {
    IMPL.vertexBufferIdQueue.enqueue(id);
}

void GarbageCollector::enqueueDestroy(UniformBufferId id) {
    IMPL.uniformBufferIdQueue.enqueue(id);
}

void GarbageCollector::enqueueDestroy(ShaderBufferId id) {
    IMPL.shaderBufferIdQueue.enqueue(id);
}

void GarbageCollector::enqueueDestroy(VertexAssemblyId id) {
    IMPL.vertexAssemblyIdQueue.enqueue(id);
}

void GarbageCollector::enqueueDestroy(Texture2DId id) {
    IMPL.texture2DIdQueue.enqueue(id);
}

void GarbageCollector::enqueueDestroy(Texture2DArrayId id) {
    IMPL.texture2DArrayIdQueue.enqueue(id);
}

void GarbageCollector::enqueueDestroy(VertexShaderId id) {
    IMPL.vertexShaderIdQueue.enqueue(id);
}

void GarbageCollector::enqueueDestroy(FragmentShaderId id) {
    IMPL.fragmentShaderIdQueue.enqueue(id);
}

void GarbageCollector::enqueueDestroy(ShaderProgramId id) {
    IMPL.shaderProgramIdQueue.enqueue(id);
}

void GarbageCollector::enqueueDestroy(UniformId id) {
    IMPL.uniformIdQueue.enqueue(id);
}
} // namespace rendell