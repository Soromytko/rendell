#include "OpenGLShaderCompilation.h"
#include <cassert>

namespace rendell {
GLuint createShader(const char *src, GLuint type) {
    assert(src);
    GLuint result = glCreateShader(type);
    const GLchar *srcPtr = static_cast<const GLchar *>(src);
    glShaderSource(result, 1, &srcPtr, NULL);
    assert(glIsShader(result) == GL_TRUE);
    return result;
}

bool compileShader(GLuint shaderId, std::string *infoLog) {
    assert(glIsShader(shaderId) == GL_TRUE);
    GLint success;
    glCompileShader(shaderId);
    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);
    if (infoLog) {
        infoLog->clear();
        GLint logLength = 0;
        glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &logLength);
        if (logLength > 1) {
            std::string log(logLength, '\0');
            glGetShaderInfoLog(shaderId, logLength, nullptr, log.data());
            *infoLog = log;
        }
    }
    return success == GL_TRUE;
}
} // namespace rendell
