#pragma once
#include "IContext.h"
#include "OpenGL/OpenGLContext.h"
#include <rendell/init_types.h>

namespace rendell {
OpenGLContextUniquePtr createOpenGLContext(const NativeView &nativeView);
} // namespace rendell