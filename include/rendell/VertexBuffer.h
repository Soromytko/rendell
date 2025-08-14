#pragma once
#include "VertexBufferLayout.h"
#include "private/defines.h"
#include <memory>
#include <vector>

namespace rendell {
class VertexBuffer {
public:
    VertexBuffer(std::vector<float> &&data);
    virtual ~VertexBuffer() = default;

    virtual void bind() const = 0;
    virtual void unbind() const = 0;
    const std::vector<float> &getData() const;
    int getStride() const;
    const std::vector<VertexBufferLayout> &getLayouts() const;
    void setLayouts(const std::vector<VertexBufferLayout> &layouts);

protected:
    void calculateOffsetsAndStride();

    std::vector<float> _data;
    int _stride = 0;
    std::vector<VertexBufferLayout> _layouts{};
};

RENDELL_USE_RAII(VertexBuffer)
} // namespace rendell