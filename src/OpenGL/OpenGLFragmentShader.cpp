#include "OpenGLFragmentShader.h"
#include "OpenGLShaderCompilation.h"

namespace rendell {
OpenGLFragmentShader ::OpenGLFragmentShader(ArrayRef<char> src)
    : OpenGLFragmentShader(src) {
    createShader(src.data, GL_FRAGMENT_SHADER);
}

OpenGLFragmentShader::~OpenGLFragmentShader() {
    glDeleteShader(_shaderId);
}

bool OpenGLFragmentShader::compile(std::string *infoLog) {
    return compileShader(_shaderId, infoLog);
}
} // namespace rendell
