#include <rendell/oop/FragmentShader.h>
#include <rendell/rendell.h>

namespace rendell {
namespace oop {
FragmentShader::FragmentShader(const std::string &src, ResultCallback callback) {
    _id = createFragmentShader(src, callback);
}

FragmentShader::~FragmentShader() {
    destroy(_id);
}
} // namespace oop
} // namespace rendell
