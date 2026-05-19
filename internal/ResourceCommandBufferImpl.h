#pragma once
#include <Buffers/ByteBuffer.h>
#include <ResourceDataProvider.h>
#include <config.h>

namespace rendell {
struct ResourceCommandBufferImpl {
    friend class ResourceCommandBuffer;

    ByteBuffer resourceCommandBuffer{config::resourceByteBufferReservedSize};
    ResourceDataProvider resourceDataProvider;

    void reset() { resourceCommandBuffer.reset(); }

    inline static ResourceCommandBufferImpl &getFromStorage(std::byte *storage) {
        return *reinterpret_cast<ResourceCommandBufferImpl *>(storage);
    }
};
} // namespace rendell