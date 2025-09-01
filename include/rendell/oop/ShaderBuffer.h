#pragma once
#include <rendell/DataType.h>
#include <rendell/ResourceId.h>
#include <rendell/oop/raii.h>

namespace rendell {
bool isValid(ShaderBufferId shaderBufferId);
void setShaderBuffer(ShaderBufferId shaderBufferId, uint32_t binding);

namespace oop {
class ShaderBuffer final {
public:
    ShaderBuffer(const byte_t *data, size_t size);
    ShaderBuffer(const ByteContainer &data);
    ~ShaderBuffer();

    void setSubData(const byte_t *data, size_t size, size_t offset = 0);

    inline void use(uint32_t binding) { rendell::setShaderBuffer(_id, binding); }

    inline ShaderBufferId getId() const { return _id; }

    inline bool isValid() const { return rendell::isValid(_id); }

private:
    size_t _size;
    ShaderBufferId _id;
};

RENDELL_USE_RAII_FACTORY(ShaderBuffer)
} // namespace oop
} // namespace rendell