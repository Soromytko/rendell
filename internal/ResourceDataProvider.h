#pragma once
#include "DataContainerStorage.h"
#include "raii.h"
#include <rendell/DataType.h>

#include <string>
#include <unordered_map>

namespace rendell {
struct ResourceDataProvider final {
    DataContainerStorage<index_t> indexBufferDataContainerStorage;
    DataContainerStorage<vertex_t> vertexBufferDataContainerStorage;
    DataContainerStorage<VertexBufferId> vertexBufferIdsContainerStorage;
    DataContainerStorage<VertexLayout> vertexLayoutsContainerStorage;
    DataContainerStorage<byte_t> byteContainerStorage;
    DataContainerStorage<char> stringContainerStorage;
};

RENDELL_USE_RAII_FACTORY(ResourceDataProvider)
} // namespace rendell