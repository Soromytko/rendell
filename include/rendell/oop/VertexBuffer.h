#pragma once
#include <rendell/DataType.h>
#include <rendell/ResourceId.h>
#include <rendell/oop/raii.h>

namespace rendell {
bool isValid(VertexBufferId vertexBufferId);

namespace oop {
class VertexBuffer final {
public:
    VertexBuffer(const vertex_t *data, size_t size);
    VertexBuffer(const VertexContainer &data);
    ~VertexBuffer();

    inline VertexBufferId getId() const { return _id; }

    inline bool isValid() const { return rendell::isValid(_id); }

private:
    VertexBufferId _id;
};

RENDELL_USE_RAII_FACTORY(VertexBuffer)
} // namespace oop
} // namespace rendell