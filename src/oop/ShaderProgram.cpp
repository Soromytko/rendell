#include <rendell/oop/ShaderProgram.h>
#include <rendell/rendell.h>

namespace rendell {
namespace oop {
ShaderProgram::ShaderProgram(VertexShaderSharedPtr vertexShader,
                             FragmentShaderSharedPtr fragmentShader, ResultCallback callback) {
    const auto internalCallback = [vertexShader, fragmentShader,
                                   callback](bool success, const std::string &result) {
        if (callback) {
            callback(success, result);
        }
    };
    _id = createShaderProgram(vertexShader->getId(), fragmentShader->getId(), callback);
}

ShaderProgram::~ShaderProgram() {
    destroy(_id);
}
} // namespace oop
} // namespace rendell
