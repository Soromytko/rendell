#include <DataContainerStorage.h>

namespace rendell {
static DataContainerStorage<index_t> s_indexBufferDataContainerStorage;
static DataContainerStorage<vertex_t> s_vertexBufferDataContainerStorage;
} // namespace rendell

namespace rendell {
DataContainerStorage<index_t> &getIndexBufferDataContainerStorage() {
    return s_indexBufferDataContainerStorage;
}

DataContainerStorage<vertex_t> &getVertexBufferDataContainerStorage() {
    return s_vertexBufferDataContainerStorage;
}
} // namespace rendell