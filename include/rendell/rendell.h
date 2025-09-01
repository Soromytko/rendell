#pragma once
#include "ResourceId.h"
#include "ThreadRenderer.h"
#include "init.h"

namespace rendell {
IndexBufferId createIndexBuffer(const IndexBufferData &data);
VertexBufferId createVertexBuffer(const VertexBufferData &data);
Texture2DId createTexture2D();
Texture2DArrayId createTexture2DArray();
VertexShaderId createVertexShader(const std::string &src);
FragmentShaderId createFragmentShader(const std::string &src);
ShaderProgramId createShaderProgram(VertexShaderId vertexShaderId,
                                    FragmentShaderId fragmentShaderId);
UniformId createUniform(const std::string &name, UniformType type);

void setIndexBuffer(IndexBufferId indexBufferId);
void setVertexBuffer(VertexBufferId vertexBufferId);
void setVertexArrayBuffer(VertexArrayBufferId vertexArrayBufferId);
void setShaderProgram(ShaderProgramId shaderProgramId);
void submit();

RenderContext *startThreadRender();
void endThreadRender(RenderContext *renderContext);

void prepare();
void renderFrame(NativeViewId nativeFrameId = 0);

} // namespace rendell