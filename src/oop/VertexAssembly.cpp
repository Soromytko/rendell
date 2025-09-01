#include <rendell/oop/VertexAssembly.h>
#include <rendell/rendell.h>

#include <algorithm>
#include <cassert>

namespace rendell {
namespace oop {
VertexAssembly::VertexAssembly(IndexBufferSharedPtr indexBuffer,
                               std::vector<VertexBufferSharedPtr> vertexBuffers,
                               std::vector<VertexLayout> vertexLayouts)
    : _indexBuffer(indexBuffer)
    , _vertexBuffers(vertexBuffers) {
    assert(indexBuffer);
    std::vector<VertexBufferId> vertexBufferIds(vertexBuffers.size());
    std::transform(vertexBuffers.begin(), vertexBuffers.end(), vertexBufferIds.begin(),
                   [](const VertexBufferSharedPtr &vertexBuffer) {
                       assert(vertexBuffer);
                       return vertexBuffer->getId();
                   });
    _id = createVertexAssembly(_indexBuffer->getId(), vertexBufferIds, vertexLayouts);
}

VertexAssembly::~VertexAssembly() {
    destroy(_id);
}
} // namespace oop
} // namespace rendell
