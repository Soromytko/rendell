#include <rendell/oop/ShaderProgram.h>
#include <rendell/rendell.h>

namespace rendell {
namespace oop {
ShaderProgram::ShaderProgram(VertexShaderId vertexShaderId, FragmentShaderId fragmentShaderId,
                             ResultCallback callback) {
    const auto internalCallback = [callback](bool success, const std::string &result) {
        if (callback) {
            callback(success, result);
        }
    };
    _id = createShaderProgram(vertexShaderId, fragmentShaderId, callback);
}

ShaderProgram::~ShaderProgram() {
    destroy(_id);
}
} // namespace oop
} // namespace rendell
