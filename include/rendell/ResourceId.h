#pragma once
#include <cstdint>
#include <type_traits>

#define RENDELL_DECLARE_FINAL_RESOURCE_ID(name)                                                    \
    struct name final : public ResourceId {};

#define RENDELL_DECLARE_RESOURCE_ID(name)                                                          \
    struct name : public ResourceId {};

#define RENDELL_DECLARE_UNIFORM_RESOURCE_ID(name)                                                  \
    struct name final : public UniformId {};

namespace rendell {
struct ResourceId {
    uint16_t index{0};
    uint16_t version{0};

    bool operator==(const ResourceId &) const = default;
};

struct UniformId : public ResourceId {};

RENDELL_DECLARE_RESOURCE_ID(IndexBufferId)
RENDELL_DECLARE_RESOURCE_ID(VertexBufferId)
RENDELL_DECLARE_FINAL_RESOURCE_ID(VertexAssemblyId)
RENDELL_DECLARE_FINAL_RESOURCE_ID(ShaderBufferId)
RENDELL_DECLARE_FINAL_RESOURCE_ID(Texture2DId)
RENDELL_DECLARE_FINAL_RESOURCE_ID(Texture2DArrayId)
RENDELL_DECLARE_FINAL_RESOURCE_ID(UniformBufferId)
RENDELL_DECLARE_FINAL_RESOURCE_ID(VertexShaderId)
RENDELL_DECLARE_FINAL_RESOURCE_ID(FragmentShaderId)
RENDELL_DECLARE_FINAL_RESOURCE_ID(ShaderProgramId)

struct DynamicIndexBufferId final : public IndexBufferId {};

struct DynamicVertexBufferId final : public VertexBufferId {};

RENDELL_DECLARE_UNIFORM_RESOURCE_ID(UniformInt1Id)
RENDELL_DECLARE_UNIFORM_RESOURCE_ID(UniformInt2Id)
RENDELL_DECLARE_UNIFORM_RESOURCE_ID(UniformInt3Id)
RENDELL_DECLARE_UNIFORM_RESOURCE_ID(UniformInt4Id)
RENDELL_DECLARE_UNIFORM_RESOURCE_ID(UniformFloat1Id)
RENDELL_DECLARE_UNIFORM_RESOURCE_ID(UniformFloat2Id)
RENDELL_DECLARE_UNIFORM_RESOURCE_ID(UniformFloat3Id)
RENDELL_DECLARE_UNIFORM_RESOURCE_ID(UniformFloat4Id)
RENDELL_DECLARE_UNIFORM_RESOURCE_ID(UniformMat4Id)
RENDELL_DECLARE_UNIFORM_RESOURCE_ID(UniformSampler2DId)

} // namespace rendell
