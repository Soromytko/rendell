#include "context_creation.h"
#include "IContext.h"
#include <rendell/init.h>

namespace rendell {
IContextUniquePtr createContext(const Initer &initer) {
    switch (initer.api) {
    case SpecificationAPI::OpenGL:
        return createOpenGLContext(initer);
    }
    return nullptr;
}

OpenGLContextUniquePtr createOpenGLContext(const Initer &initer) {
#if defined(_WIN32)
    return makeUniqueWindowsOpenGLContext(initer);
#elif defined(__linux__)
    return makeUniqueLinuxOpenGLContext(initer);
#endif
    return nullptr;
}
} // namespace rendell