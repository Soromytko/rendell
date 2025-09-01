
#pragma once
#include <rendell/Ref.h>
#include <rendell/ResourceId.h>
#include <rendell/TextureFormat.h>

namespace rendell {
enum class CmdType {
    // Create stuff
    createIndexBufferCmdType,
    createVertexBufferCmdType,
    createVertexArrayBufferCmdType,
    createTexture2DCmdType,
    createTexture2DArrayCmdType,
    createUniformBufferCmdType,
    createVertexShaderCmdType,
    createFragmentShaderCmdType,
    createShaderProgramCmdType,
    createUniformCmdType,

    // Uniform
    setVec2UniformCmdType,
    setVec3UniformCmdType,
    setVec4UniformCmdType,
};

struct Command final {
    CmdType type;
    void *data;
};
} // namespace rendell

// Creation
namespace rendell {
struct CreateIndexBufferCmdData final {
    static const CmdType type = CmdType::createIndexBufferCmdType;
    IndexBufferId id;
    ArrayRef<uint32_t> data;
};

struct CreateVertexBufferCmdData final {
    static const CmdType type = CmdType::createVertexBufferCmdType;
    VertexBufferId id;
    ArrayRef<float> data;
};

struct CreateVertexArrayBufferCmdData final {
    static const CmdType type = CmdType::createVertexArrayBufferCmdType;
    VertexArrayBufferId id;
    IndexBufferId indexBufferId;
    ArrayRef<VertexBufferId> vertexBuffers;
};

struct CreateTexture2DCmdData final {
    static const CmdType type = CmdType::createTexture2DCmdType;
    Texture2DId id;
    uint32_t width;
    uint32_t height;
    TextureFormat format;
    ArrayRef<uint8_t> data;
};

struct CreateTexture2DArrayCmdData final {
    static const CmdType type = CmdType::createTexture2DArrayCmdType;
    Texture2DArrayId id;
    uint32_t width;
    uint32_t height;
    uint32_t count;
    TextureFormat format;
    ArrayRef<uint8_t> data;
};

struct CreateVertexShaderCmdData final {
    static const CmdType type = CmdType::createVertexShaderCmdType;
    VertexShaderId id;
    ArrayRef<char> src;
};

struct CreateFragmentShaderCmdData final {
    static const CmdType type = CmdType::createFragmentShaderCmdType;
    FragmentShaderId id;
    ArrayRef<char> src;
};

struct CreateShaderProgramCmdData final {
    static const CmdType type = CmdType::createShaderProgramCmdType;
    ShaderProgramId id;
    VertexShaderId vertexShaderId;
    FragmentShaderId fragmentShaderId;
};

struct CreateUniformCmdData final {
    static const CmdType type = CmdType::createUniformCmdType;
    UniformId id;
    UniformType dataType;
};
} // namespace rendell

// Uniforms
namespace rendell {
struct Vec2UniformCommand final {
    static const CmdType type = CmdType::setVec2UniformCmdType;
    float x, y;
};

struct Vec3UniformCommand final {
    static const CmdType type = CmdType::setVec3UniformCmdType;
    float x, y, z;
};

struct Vec4UniformCommand final {
    static const CmdType type = CmdType::setVec4UniformCmdType;
    float x, y, z, w;
};
} // namespace rendell