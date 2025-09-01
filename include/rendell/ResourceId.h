#pragma once
#include <cstdint>

#define DECLARE_RESOURCE_ID(name)                                                                  \
    struct name final : public ResourceId {};

namespace rendell {
struct ResourceId {
    uint16_t index;
    uint16_t version;
};

DECLARE_RESOURCE_ID(IndexBufferId)
DECLARE_RESOURCE_ID(VertexBufferId)
DECLARE_RESOURCE_ID(VertexArrayBufferId)
DECLARE_RESOURCE_ID(Texture2DId)
DECLARE_RESOURCE_ID(Texture2DArrayId)
DECLARE_RESOURCE_ID(ShaderBufferId)
DECLARE_RESOURCE_ID(UniformBufferId)
DECLARE_RESOURCE_ID(VertexShaderId)
DECLARE_RESOURCE_ID(FragmentShaderId)
DECLARE_RESOURCE_ID(ShaderProgramId)
DECLARE_RESOURCE_ID(UniformId)
} // namespace rendell
