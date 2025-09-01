#pragma once
#include <glad/glad.h>
#include <rendell/oop/raii.h>

#include <string>
#include <string_view>

namespace rendell {
class OpenGLFragmentShader final {
public:
    OpenGLFragmentShader(std::string_view src);
    ~OpenGLFragmentShader();

    inline GLuint getId() const { return _shaderId; }

    bool compile(std::string *infoLog = nullptr);

private:
    GLuint _shaderId{};
};
RENDELL_USE_RAII_FACTORY(OpenGLFragmentShader)
} // namespace rendell
