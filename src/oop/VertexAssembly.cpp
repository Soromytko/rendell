#include <rendell/oop/VertexAssembly.h>
#include <rendell/rendell.h>

namespace rendell {
namespace oop {
VertexAssembly::VertexAssembly(IndexBufferId indexBufferId,
                               std::vector<VertexBufferId> vertexBufferIds,
                               std::vector<VertexLayout> vertexLayouts) {
    _id = createVertexAssembly(indexBufferId, std::move(vertexBufferIds), std::move(vertexLayouts));
}

VertexAssembly::~VertexAssembly() {
    destroy(_id);
}
} // namespace oop
} // namespace rendell
