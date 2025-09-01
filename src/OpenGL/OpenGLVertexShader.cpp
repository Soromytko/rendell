#include <OpenGL/OpenGLVertexShader.h>

#include "OpenGLShaderCompilation.h"

namespace rendell {
OpenGLVertexShader::OpenGLVertexShader(std::string_view src) {
    _shaderId = createShader(src.data(), GL_VERTEX_SHADER);
}

OpenGLVertexShader::~OpenGLVertexShader() {
    glDeleteShader(_shaderId);
}

bool OpenGLVertexShader::compile(std::string *infoLog) {
    return compileShader(_shaderId, infoLog);
}
} // namespace rendell
