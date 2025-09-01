#pragma once
#include <rendell/ResourceId.h>
#include <rendell/TextureFormat.h>
#include <rendell/VertexLayout.h>

namespace rendell {
enum class CmdType {
    // Create stuff
    createIndexBufferCmdType,
    createVertexBufferCmdType,
    createVertexAssemblyCmdType,
    createShaderBufferCmdType,
    createUniformBufferCmdType,
    createTexture2DCmdType,
    createTexture2DArrayCmdType,
    createVertexShaderCmdType,
    createFragmentShaderCmdType,
    createShaderProgramCmdType,
    createUniformCmdType,

    // Set SubData
    setIndexBufferSubDataCmdType,
    setVertexBufferSubDataCmdType,
    setShaderBufferSubDataCmdType,
    setTexture2DSubDataCmdType,
    setTexture2DArraySubDataCmdType,

    // Destroy stuff
    destroyIndexBufferCmdType,
    destroyVertexBufferCmdType,
    destroyUniformBufferCmdType,
    destroyShaderBufferCmdType,
    destroyVertexAssemblyCmdType,
    destroyTexture2DCmdType,
    destroyTexture2DArrayCmdType,
    destroyVertexShaderCmdType,
    destroyFragmentShaderCmdType,
    destroyShaderProgramCmdType,
    destroyUniformCmdType,
};

enum class RenderCmdType {
    clearColorCmdType,
    setViewportCmdType,
    setScissorsCmdType,
    useShaderBufferCmdType,
    useUniformBufferCmdType,
    setTexture2DCmdType,
    setTexture2DArrayCmdType,
};

struct Command final {
    CmdType type;
    void *data;
};
} // namespace rendell

// Creation
namespace rendell {
using data_key_t = size_t;

struct CreateIndexBufferCmdData final {
    inline static const CmdType type = CmdType::createIndexBufferCmdType;
    IndexBufferId id;
    bool isDynamic;
    size_t dataSize;
    data_key_t dataKey;
};

struct CreateVertexBufferCmdData final {
    inline static const CmdType type = CmdType::createVertexBufferCmdType;
    VertexBufferId id;
    bool isDynamic;
    size_t dataSize;
    data_key_t dataKey;
};

struct CreateUniformBufferCmdData final {
    inline static const CmdType type = CmdType::createUniformBufferCmdType;
    UniformBufferId id;
    data_key_t dataKey;
};

struct CreateShaderBufferCmdData final {
    inline static const CmdType type = CmdType::createShaderBufferCmdType;
    ShaderBufferId id;
    size_t dataSize;
    data_key_t dataKey;
};

struct CreateVertexAssemblyCmdData final {
    inline static const CmdType type = CmdType::createVertexAssemblyCmdType;
    VertexAssemblyId id;
    IndexBufferId indexBufferId;
    size_t vertexBufferIdsKey;
    size_t vertexLayoutsKey;
};

struct CreateTexture2DCmdData final {
    inline static const CmdType type = CmdType::createTexture2DCmdType;
    Texture2DId id;
    uint32_t width;
    uint32_t height;
    TextureFormat format;
    data_key_t dataKey;
};

struct CreateTexture2DArrayCmdData final {
    inline static const CmdType type = CmdType::createTexture2DArrayCmdType;
    Texture2DArrayId id;
    uint32_t width;
    uint32_t height;
    uint32_t count;
    TextureFormat format;
};

struct CreateVertexShaderCmdData final {
    inline static const CmdType type = CmdType::createVertexShaderCmdType;
    VertexShaderId id;
    size_t srcKey;
};

struct CreateFragmentShaderCmdData final {
    inline static const CmdType type = CmdType::createFragmentShaderCmdType;
    FragmentShaderId id;
    size_t srcKey;
};

struct CreateShaderProgramCmdData final {
    inline static const CmdType type = CmdType::createShaderProgramCmdType;
    ShaderProgramId id;
    VertexShaderId vertexShaderId;
    FragmentShaderId fragmentShaderId;
};

struct CreateUniformCmdData final {
    inline static const CmdType type = CmdType::createUniformCmdType;
    UniformId id;
    UniformType dataType;
    size_t nameKey;
};

struct SetIndexBufferSubDataCmdData final {
    inline static const CmdType type = CmdType::setIndexBufferSubDataCmdType;
    DynamicIndexBufferId id;
    size_t offset;
    data_key_t dataKey;
};

struct SetVertexBufferSubDataCmdData final {
    inline static const CmdType type = CmdType::setVertexBufferSubDataCmdType;
    DynamicVertexBufferId id;
    size_t offset;
    data_key_t dataKey;
};

struct SetShaderBufferSubDataCmdData final {
    inline static const CmdType type = CmdType::setShaderBufferSubDataCmdType;
    ShaderBufferId id;
    size_t offset;
    data_key_t dataKey;
};

struct SetTexture2DSubDataCmdData final {
    inline static const CmdType type = CmdType::setTexture2DSubDataCmdType;
    Texture2DId id;
    uint32_t width;
    uint32_t height;
    uint32_t widthOffset;
    uint32_t heightOffset;
    data_key_t dataKey;
};

struct SetTexture2DArraySubDataCmdData final {

    inline static const CmdType type = CmdType::setTexture2DArraySubDataCmdType;
    Texture2DArrayId id;
    uint32_t index;
    uint32_t width;
    uint32_t height;
    uint32_t widthOffset;
    uint32_t heightOffset;
    data_key_t dataKey;
};

struct DestroyIndexBufferCmdData final {
    inline static const CmdType type = CmdType::destroyIndexBufferCmdType;
    IndexBufferId id;
};

struct DestroyVertexBufferCmdData final {
    inline static const CmdType type = CmdType::destroyVertexBufferCmdType;
    VertexBufferId id;
};

struct DestroyUniformBufferCmdData final {
    inline static const CmdType type = CmdType::destroyUniformBufferCmdType;
    UniformBufferId id;
};

struct DestroyShaderBufferCmdData final {
    inline static const CmdType type = CmdType::destroyShaderBufferCmdType;
    ShaderBufferId id;
};

struct DestroyVertexAssemblyCmdData final {
    inline static const CmdType type = CmdType::destroyVertexAssemblyCmdType;
    VertexAssemblyId id;
};

struct DestroyTexture2DCmdData final {
    inline static const CmdType type = CmdType::destroyTexture2DCmdType;
    Texture2DId id;
};

struct DestroyTexture2DArrayCmdData final {
    inline static const CmdType type = CmdType::destroyTexture2DArrayCmdType;
    Texture2DArrayId id;
};

struct DestroyVertexShaderCmdData final {
    inline static const CmdType type = CmdType::destroyVertexShaderCmdType;
    VertexShaderId id;
};

struct DestroyFragmentShaderCmdData final {
    inline static const CmdType type = CmdType::destroyFragmentShaderCmdType;
    FragmentShaderId id;
};

struct DestroyShaderProgramCmdData final {
    inline static const CmdType type = CmdType::destroyShaderProgramCmdType;
    ShaderProgramId id;
};

struct DestroyUniformCmdData final {
    inline static const CmdType type = CmdType::destroyUniformCmdType;
    UniformId id;
};
} // namespace rendell

namespace rendell {
struct ClearColorCmdData final {
    inline static const RenderCmdType type = RenderCmdType::clearColorCmdType;
    float r;
    float g;
    float b;
    float a;
};

struct SetViewportCmdData final {
    inline static const RenderCmdType type = RenderCmdType::setViewportCmdType;
    uint32_t x;
    uint32_t y;
    uint32_t width;
    uint32_t height;
};

struct SetScissorsCmdData final {
    inline static const RenderCmdType type = RenderCmdType::setScissorsCmdType;
    uint32_t x;
    uint32_t y;
    uint32_t width;
    uint32_t height;
};

struct UseShaderBufferCmdData final {
    inline static const RenderCmdType type = RenderCmdType::useShaderBufferCmdType;
    ShaderBufferId id;
    uint32_t binding;
};

struct UseUniformBufferCmdData final {
    inline static const RenderCmdType type = RenderCmdType::useUniformBufferCmdType;
    UniformBufferId id;
    uint32_t binding;
};

struct SetTexture2DCmdData final {
    inline static const RenderCmdType type = RenderCmdType::setTexture2DCmdType;
    UniformSampler2DId samplerId;
    Texture2DId textureId;
    uint32_t stage;
};

struct SetTexture2DArrayCmdData final {
    inline static const RenderCmdType type = RenderCmdType::setTexture2DArrayCmdType;
    UniformSampler2DId samplerId;
    Texture2DArrayId textureId;
    uint32_t stage;
};
} // namespace rendell