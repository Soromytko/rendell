#pragma once
#include "IContext.h"
#include "OpenGL/OpenGLContext.h"

namespace rendell
{
#if defined(_WIN32)
	using OpenGLContext = WindowsOpenGLContext;
	using OpenGLContextSharedPtr = WindowsOpenGLContextSharedPtr;
#elif defined(__linux__)
	using OpenGLContext = LinuxOpenGLContext;
	using OpenGLContextSharedPtr = LinuxOpenGLContextSharedPtr;
#else
#error "Unknown or unsupported operating system!"
#endif

	IContextSharedPtr createContext(const Initer& initer);
	OpenGLContextSharedPtr createOpenGLContext(const Initer& initer);
}