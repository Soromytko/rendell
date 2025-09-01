#pragma once
#include <glad/glad.h>
#include <string>

namespace rendell {
GLuint createShader(const char *src, GLuint type);
bool compileShader(GLuint shaderId, std::string *infoLog);
} // namespace rendell