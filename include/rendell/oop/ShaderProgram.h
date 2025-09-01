#pragma once
#include <rendell/DataType.h>
#include <rendell/ResourceId.h>
#include <rendell/oop/FragmentShader.h>
#include <rendell/oop/VertexShader.h>
#include <rendell/oop/raii.h>

namespace rendell {
bool isValid(ShaderProgramId texture2DId);
void setShaderProgram(ShaderProgramId texture2DId);

namespace oop {
class ShaderProgram final {
public:
    ShaderProgram(VertexShaderSharedPtr vertexShader, FragmentShaderSharedPtr fragmentShader,
                  ResultCallback callback = nullptr);
    ~ShaderProgram();

    inline void use() { rendell::setShaderProgram(_id); }

    inline ShaderProgramId getId() const { return _id; }

    inline bool isValid() const { return rendell::isValid(_id); }

private:
    ShaderProgramId _id;
};

RENDELL_USE_RAII_FACTORY(ShaderProgram)
} // namespace oop
} // namespace rendell