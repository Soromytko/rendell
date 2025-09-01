#pragma once
#include <raii.h>
#include <rendell/Ref.h>
#include <string>

namespace rendell {
class FragmentShader {
public:
    FragmentShader(ArrayRef<char> src) {}

    virtual ~FragmentShader() = default;

    virtual bool compile(std::string *result) = 0;
};
RENDELL_USE_RAII(FragmentShader)
} // namespace rendell