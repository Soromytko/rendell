#pragma once
#include <cstdint>
#include <memory>
#include <raii.h>
#include <rendell/Ref.h>
#include <vector>

namespace rendell {
class IndexBuffer {
public:
    IndexBuffer(ArrayRef<uint32_t> indices);
    virtual ~IndexBuffer() = default;

    virtual void bind() const = 0;
    virtual void unbind() const = 0;

    virtual void setData(ArrayRef<uint32_t> indices) = 0;
};

RENDELL_USE_RAII(IndexBuffer)
} // namespace rendell