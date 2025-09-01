#pragma once
#include <rendell/DataType.h>
#include <rendell/ResourceId.h>
#include <rendell/oop/raii.h>

#include <string>

namespace rendell {
bool isValid(FragmentShaderId fragmentShaderId);

namespace oop {
class FragmentShader final {
public:
    FragmentShader(const std::string &src, ResultCallback callback = nullptr);
    ~FragmentShader();

    inline FragmentShaderId getId() const { return _id; }

    inline bool isValid() const { return rendell::isValid(_id); }

private:
    FragmentShaderId _id;
};

RENDELL_USE_RAII_FACTORY(FragmentShader)
} // namespace oop
} // namespace rendell