#pragma once
#include "DataContainerStorage.h"
#include <rendell/DataType.h>
#include <rendell/ResourceId.h>
#include <rendell/VertexLayout.h>

namespace rendell {
struct ResourceDataProvider final {
    DataContainerStorage<index_t> indexBufferDataContainerStorage;
    DataContainerStorage<vertex_t> vertexBufferDataContainerStorage;
    DataContainerStorage<VertexBufferId> vertexBufferIdsContainerStorage;
    DataContainerStorage<VertexLayout> vertexLayoutsContainerStorage;
    DataContainerStorage<byte_t> byteContainerStorage;
    DataContainerStorage<char> stringContainerStorage;
};
} // namespace rendell