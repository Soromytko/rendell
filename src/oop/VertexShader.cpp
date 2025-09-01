#include <rendell/oop/VertexShader.h>
#include <rendell/rendell.h>

namespace rendell {
namespace oop {
VertexShader::VertexShader(const std::string &src, ResultCallback callback) {
    _id = createVertexShader(src, callback);
}

VertexShader::~VertexShader() {
    destroy(_id);
}
} // namespace oop
} // namespace rendell
