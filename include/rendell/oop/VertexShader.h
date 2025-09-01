#pragma once
#include <rendell/DataType.h>
#include <rendell/ResourceId.h>
#include <rendell/oop/raii.h>

#include <string>

namespace rendell {
bool isValid(VertexShaderId vertexShaderId);

namespace oop {
class VertexShader final {
public:
    VertexShader(const std::string &src, ResultCallback callback = nullptr);
    ~VertexShader();

    inline VertexShaderId getId() const { return _id; }

    inline bool isValid() const { return rendell::isValid(_id); }

private:
    VertexShaderId _id;
};

RENDELL_USE_RAII_FACTORY(VertexShader)
} // namespace oop
} // namespace rendell