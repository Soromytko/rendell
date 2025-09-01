#pragma once
#include <rendell/DataType.h>
#include <rendell/ResourceId.h>
#include <rendell/oop/raii.h>

namespace rendell {
bool isValid(UniformBufferId uniformBufferId);
void setUniformBuffer(UniformBufferId uniformBufferId, uint32_t binding);

namespace oop {
class UniformBuffer final {
public:
    UniformBuffer(const byte_t *data, size_t size);
    UniformBuffer(const ByteContainer &data);
    ~UniformBuffer();

    inline void use(uint32_t binding) { rendell::setUniformBuffer(_id, binding); }

    inline UniformBufferId getId() const { return _id; }

    inline bool isValid() const { return rendell::isValid(_id); }

private:
    UniformBufferId _id;
};

RENDELL_USE_RAII_FACTORY(UniformBuffer)
} // namespace oop
} // namespace rendell