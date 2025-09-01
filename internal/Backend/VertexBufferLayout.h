#pragma once
#include <cstdint>
#include <string>
#include <vector>

namespace rendell {
enum class ShaderDataType {
    int1,
    int2,
    int3,
    int4,
    float1,
    float2,
    float3,
    float4,

};

class VertexBufferLayout {
public:
    VertexBufferLayout(ShaderDataType type, bool normalized = false, size_t offset = 0);
    ShaderDataType getType() const;
    size_t getSize() const;
    size_t getOffset() const;
    bool getNormalized() const;
    int getComponentCountByShaderType() const;
    void setOffset(size_t value);

private:
    ShaderDataType _type;
    // std::string name;
    size_t _size;
    size_t _offset;
    bool _normalized;
};
} // namespace rendell
