#include "OpenGLShaderCompilation.h"

#define LOG_INFO_BUFFER_SIZE 512

namespace rendell {
GLuint createShader(const char *src, GLuint type) {
    GLuint result = glCreateShader(type);
    const GLchar *srcPtr = static_cast<const GLchar *>(src);
    glShaderSource(result, 1, &srcPtr, NULL);
    return result;
}

bool compileShader(GLuint shaderId, std::string *infoLog) {
    int success;
    glCompileShader(shaderId);
    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);
    if (!success && infoLog) {
        char infoLogBuffer[LOG_INFO_BUFFER_SIZE];
        glGetShaderInfoLog(shaderId, LOG_INFO_BUFFER_SIZE, NULL, infoLogBuffer);
        *infoLog = infoLogBuffer;
    }
    return success;
}
} // namespace rendell
