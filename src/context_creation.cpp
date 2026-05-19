#include "context_creation.h"

#include <memory>

namespace rendell {
OpenGLContextUniquePtr createOpenGLContext(const NativeView &nativeView) {
#if defined(_WIN32)
    return std::make_unique<WindowsOpenGLContext>(nativeView);
#elif defined(__linux__)
    return std::make_unique<LinuxOpenGLContext>(nativeView);
#endif
    return nullptr;
}
} // namespace rendell