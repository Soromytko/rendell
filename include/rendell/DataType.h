#pragma once
#include "DataContainer.h"

#include <cstddef>
#include <functional>
#include <memory>
#include <string>
#include <vector>

namespace rendell {
using index_t = uint32_t;
using vertex_t = float;
using byte_t = std::byte;
using IndexContainer = DataContainer<index_t>;
using VertexContainer = DataContainer<vertex_t>;
using StringContainer = DataContainer<char>;
using ByteContainer = DataContainer<byte_t>;

using bitfield = size_t;

using ResultCallback = std::function<void(bool success, const std::string &infoLog)>;

enum class UniformType {
    int1,
    int2,
    int3,
    int4,
    float1,
    float2,
    float3,
    float4,
    mat4,
    sampler2D,
};

using ShaderDataType = UniformType;

} // namespace rendell
