#include <OpenGL/OpenGLFragmentShader.h>

#include "OpenGLShaderCompilation.h"

namespace rendell {
OpenGLFragmentShader ::OpenGLFragmentShader(std::string_view src) {
    _shaderId = createShader(src.data(), GL_FRAGMENT_SHADER);
}

OpenGLFragmentShader::~OpenGLFragmentShader() {
    glDeleteShader(_shaderId);
}

bool OpenGLFragmentShader::compile(std::string *infoLog) {
    return compileShader(_shaderId, infoLog);
}
} // namespace rendell
