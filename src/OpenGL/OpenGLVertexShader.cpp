#include "OpenGLVertexShader.h"
#include "OpenGLShaderCompilation.h"

namespace rendell {
OpenGLVertexShader::OpenGLVertexShader(ArrayRef<char> src)
    : VertexShader(src) {
    _shaderId = createShader(src.data, GL_VERTEX_SHADER);
}

OpenGLVertexShader::~OpenGLVertexShader() {
    glDeleteShader(_shaderId);
}

bool OpenGLVertexShader::compile(std::string *infoLog) {
    return compileShader(_shaderId, infoLog);
}
} // namespace rendell
