#pragma once
#include <rendell/DataType.h>
#include <rendell/ResourceId.h>
#include <rendell/oop/raii.h>

namespace rendell {
bool isValid(IndexBufferId indexBufferId);

namespace oop {
class IndexBuffer final {
public:
    IndexBuffer(const index_t *data, size_t size);
    IndexBuffer(const IndexContainer &data);
    ~IndexBuffer();

    inline IndexBufferId getId() const { return _id; }

    inline bool isValid() const { return rendell::isValid(_id); }

private:
    IndexBufferId _id;
};

RENDELL_USE_RAII_FACTORY(IndexBuffer)
} // namespace oop
} // namespace rendell