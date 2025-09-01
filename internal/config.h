#pragma once
#include <cstddef>

namespace rendell {
namespace config {
constexpr size_t byteRingBufferChunkCapacity = 1024;
constexpr size_t ringBufferChunkCapacity = 1024;
constexpr size_t drawCallStateListCapacity = 1 << 16;
constexpr size_t resourceByteBufferReservedSize = 1 << 16;
constexpr size_t resourceContextPoolSize = 10;
constexpr size_t renderContextPoolSize = 10;
constexpr size_t uniformBufferSize = 1 << 16;
constexpr size_t renderCommandBufferSize = 1 << 16;
constexpr size_t maxUniformNameLength = 255;
constexpr uint16_t resourceStorageIdCapacity = 1024;
} // namespace config
} // namespace rendell