#pragma once
#include <raii.h>
#include <rendell/Ref.h>
#include <string>

namespace rendell {
class VertexShader {
public:
    VertexShader(ArrayRef<char> src) {};
    virtual ~VertexShader() = default;

    virtual bool compile(std::string *result = nullptr) = 0;
};
RENDELL_USE_RAII(VertexShader)
} // namespace rendell