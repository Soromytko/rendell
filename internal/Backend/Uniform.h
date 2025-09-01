#pragma once
#include <rendell/DataType.h>

namespace rendell {
class Uniform final {
public:
    Uniform(std::string name, UniformType type);
    ~Uniform() = default;
};
} // namespace rendell