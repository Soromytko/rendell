#pragma once
#include "IContext.h"
#include "OpenGL/OpenGLContext.h"

namespace rendell {
#if defined(_WIN32)
using OpenGLContext = WindowsOpenGLContext;
using OpenGLContextUniquePtr = WindowsOpenGLContextUniquePtr;
#elif defined(__linux__)
using OpenGLContext = LinuxOpenGLContext;
using OpenGLContextSharedPtr = LinuxOpenGLContextSharedPtr;
#else
#error "Unknown or unsupported operating system!"
#endif

IContextUniquePtr createContext(const Initer &initer);
OpenGLContextUniquePtr createOpenGLContext(const Initer &initer);
} // namespace rendell