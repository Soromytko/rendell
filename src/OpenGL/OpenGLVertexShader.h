#pragma once
#include <Backend/VertexShader.h>
#include <glad/glad.h>
#include <raii.h>

namespace rendell {
class OpenGLVertexShader final : public VertexShader {
    OpenGLVertexShader(ArrayRef<char> src);
    ~OpenGLVertexShader();

    bool compile(std::string *result = nullptr) override;

private:
    GLuint _shaderId{};
};
RENDELL_USE_RAII_FACTORY(OpenGLVertexShader)
} // namespace rendell
