#pragma once

#if defined(_WIN32)
#include "Platform/WindowsOpenGLContext.h"
#elif defined(__linux__)
#include "Platform/LinuxOpenGLContext.h"
#else
#error "OpenGL is not supported on this platform!"
#endif