#pragma once
#include <functional>

namespace rendell {
using InfoLogCallback = std::function<void(const std::string &infoLog)>;
void setVertexShaderCompilationCallback(InfoLogCallback callback);
void setFragmentShaderCompilationCallback(InfoLogCallback callback);
void setShaderProgramLinkingCallback(InfoLogCallback callback);
} // namespace rendell