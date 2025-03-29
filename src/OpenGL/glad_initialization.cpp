#include "glad_initialization.h"
#include <glad/glad.h>
#include <iostream>

#if defined(_WIN32)
#include <Windows.h>
#include <gl/GL.h>
#elif defined(__linux)
#include <GL/glx.h>
#include <X11/Xlib.h>
#else
#error Unknown or unsupported operating system!
#endif

namespace rendell
{
	static bool s_isInitialized{ false };

#if defined(_WIN32)
	static bool init_glad_platform()
	{
		return gladLoadGL();
	}

#elif defined(__linux__)
	static bool init_glad_platform()
	{
		return gladLoadGL();
	}

#else
	static bool init_glad_platform()
	{
		std::cerr << "ERROR: Unknown or unsupported operating system!" << std::endl;
		return false;
	}
#endif

	// TODO: It should be a thread-safe function.
	bool init_glad()
	{
		if (!s_isInitialized)
		{
			s_isInitialized = init_glad_platform();
		}

		return s_isInitialized;
	}

	const char* get_OpenGL_version()
	{
		const GLubyte* version = glGetString(GL_VERSION);
		return reinterpret_cast<const char*>(version);
	}
}