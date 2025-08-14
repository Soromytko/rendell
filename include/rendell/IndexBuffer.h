#pragma once
#include "private/defines.h"
#include <cstdint>
#include <memory>
#include <vector>

namespace rendell {
class IndexBuffer {
public:
    IndexBuffer(std::vector<uint32_t> &&indices);
    virtual ~IndexBuffer() = default;

    virtual void bind() const = 0;
    virtual void unbind() const = 0;
    const std::vector<uint32_t> &getIndices() const;

protected:
    std::vector<uint32_t> _indices;
};

RENDELL_USE_RAII(IndexBuffer)
} // namespace rendell