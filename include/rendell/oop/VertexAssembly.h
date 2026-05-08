#pragma once
#include <rendell/ResourceId.h>
#include <rendell/VertexLayout.h>
#include <rendell/oop/VertexBuffer.h>
#include <rendell/oop/raii.h>

#include <vector>

namespace rendell {
bool isValid(VertexAssemblyId vertexAssemblyId);
void setVertexAssembly(VertexAssemblyId vertexAssemblyId);

namespace oop {
class VertexAssembly final {
public:
    VertexAssembly(IndexBufferId indexBufferId, std::vector<VertexBufferId> vertexBufferIds,
                   std::vector<VertexLayout> vertexLayouts = {});
    ~VertexAssembly();

    inline void use() { rendell::setVertexAssembly(_id); }

    inline VertexAssemblyId getId() const { return _id; }

    inline bool isValid() const { return rendell::isValid(_id); }

private:
    VertexAssemblyId _id;

    std::vector<VertexBufferSharedPtr> _vertexBuffers;
};

RENDELL_USE_RAII_FACTORY(VertexAssembly)
} // namespace oop
} // namespace rendell