#pragma once
#include <Backend/FragmentShader.h>
#include <glad/glad.h>
#include <raii.h>

namespace rendell {
class OpenGLFragmentShader final : public FragmentShader {
    OpenGLFragmentShader(ArrayRef<char> src);
    ~OpenGLFragmentShader();

    bool compile(std::string *infoLog = nullptr) override;

private:
    GLuint _shaderId{};
};
RENDELL_USE_RAII_FACTORY(OpenGLFragmentShader)
} // namespace rendell
