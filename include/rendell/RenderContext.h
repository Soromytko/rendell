#pragma once
#include "DataType.h"
#include "ResourceId.h"
#include <memory>
#include <initializer_list>

namespace rendell {
class RenderContext final {
    friend class RenderContextPool;

private:
    RenderContext();

public:
    ~RenderContext() = default;

    IndexBufferId createIndexBuffer(const IndexBufferData &data);
    VertexBufferId createVertexBuffer(const VertexBufferData &data);
    VertexArrayBufferId
    createVertexArrayBuffer(IndexBufferId indexBufferId,
                            std::initializer_list<VertexBufferId> vertexBuffers);
    Texture2DId createTexture2D();
    Texture2DArrayId createTexture2DArray();
    VertexShaderId createVertexShader(const std::string &src);
    FragmentShaderId createFragmentShader(const std::string &src);
    ShaderProgramId createShaderProgram(VertexShaderId vertexShaderId,
                                        FragmentShaderId fragmentShaderId);
    UniformId createUniform(const std::string &name, UniformType type);

    void setShaderProgram(ShaderProgramId shaderProgram);
    void setIndexBuffer(IndexBufferId indexBuffer);
    void setVertexArray(VertexArrayBufferId vertexArray);

    void submit(ShaderProgramId shaderProgram);
    void submit();

private:
    struct Impl;
    std::unique_ptr<Impl> _impl;
};
} // namespace rendell