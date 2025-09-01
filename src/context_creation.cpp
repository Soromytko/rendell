#include "context_creation.h"

namespace rendell {
OpenGLContextUniquePtr createOpenGLContext(const NativeView &nativeView) {
#if defined(_WIN32)
    return makeUniqueWindowsOpenGLContext(nativeView);
#elif defined(__linux__)
    return makeUniqueLinuxOpenGLContext(nativeView);
#endif
    return nullptr;
}
} // namespace rendell