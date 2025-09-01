#pragma once
#include <rendell/DataType.h>

#include <cstdint>
#include <string>
#include <vector>

namespace rendell {
class OpenGLVertexBufferLayout {
public:
    OpenGLVertexBufferLayout(ShaderDataType type, bool normalized = false, size_t offset = 0);
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
