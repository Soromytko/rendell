#pragma once
#include <rendell/init_types.h>

#if defined(_WIN32)
#include "Platform/WindowsOpenGLContext.h"
#elif defined(__linux__)
#include "Platform/LinuxOpenGLContext.h"
#else
#error "OpenGL is not supported on this platform!"
#endif

namespace rendell {
#if defined(_WIN32)
using OpenGLContext = WindowsOpenGLContext;
using OpenGLContextUniquePtr = WindowsOpenGLContextUniquePtr;
#elif defined(__linux__)
using OpenGLContext = LinuxOpenGLContext;
using OpenGLContextUniquePtr = LinuxOpenGLContextUniquePtr;
#else
#error "Unknown or unsupported operating system!"
#endif
} // namespace rendell