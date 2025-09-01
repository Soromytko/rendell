#pragma once
#include "Buffers/Buffer.h"
#include <rendell/Color.h>
#include <rendell/DataType.h>
#include <rendell/DrawType.h>
#include <rendell/ResourceId.h>

#include <memory>

namespace rendell {
struct DrawCallState final {
    ShaderProgramId shaderProgramId{};
    VertexAssemblyId vertexAssemblyId{};
    size_t uniformBufferOffset{0};
    size_t uniformBufferSize{0};
    size_t commandBufferOffset{0};
    size_t commandBufferSize{0};
    bitfield clearBits{0};
    DrawMode drawMode{DrawMode::Elements};
    PrimitiveTopology primitiveTopology{PrimitiveTopology::Triangles};
    uint32_t instanceCount{0};

    void reset() { *this = DrawCallState(); }
};

using DrawCallStateList = Buffer<DrawCallState>;
} // namespace rendell