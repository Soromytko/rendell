#pragma once
#include <glad/glad.h>

#include <string>
#include <string_view>

namespace rendell {
class OpenGLVertexShader final {
public:
    OpenGLVertexShader(std::string_view src);
    ~OpenGLVertexShader();

    inline GLuint getId() const { return _shaderId; }

    bool compile(std::string *result = nullptr);

private:
    GLuint _shaderId{};
};
} // namespace rendell
