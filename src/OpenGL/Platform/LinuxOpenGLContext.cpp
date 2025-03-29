#include "LinuxOpenGLContext.h"
#include <iostream>
#include <cstring>
#include "../OpenGLSpecification.h"
#include "../glad_initialization.h"

namespace rendell
{
	static OpenGLSpecification s_openGLSpecification{};

	LinuxOpenGLContext::LinuxOpenGLContext(const Initer& initer)
	{
		if (initer.nativeWindowHandle == nullptr)
		{
			std::cerr << "ERROR: Initer::nativeWindowHandle field is nullptr" << std::endl;
			return;
		}
		_window = static_cast<Window>(reinterpret_cast<size_t>(initer.nativeWindowHandle));

		if (initer.x11Display == nullptr)
		{
			std::cerr << "ERROR: Initer::x11Display field is nullptr" << std::endl;
			return;
		}
		_display = reinterpret_cast<Display*>(initer.x11Display);

		_isInitialized = init();
		if (!_isInitialized)
		{
			std::cerr << "ERROR: Failed to initialize X11 OpenGL context" << std::endl;
		}
	}

	LinuxOpenGLContext::~LinuxOpenGLContext()
	{
		if (_isInitialized)
		{
			releaseContext();
		}
	}

	Specification* LinuxOpenGLContext::getSpecification() const
	{
		return &s_openGLSpecification;
	}

	std::string LinuxOpenGLContext::getName() const
	{
		return "OpenGL version: " + std::string(get_OpenGL_version());
	}

	bool LinuxOpenGLContext::isInitialized() const
	{
		return _isInitialized;
	}

	bool LinuxOpenGLContext::makeCurrent()
	{
		if (!glXMakeCurrent(_display, _window, _glContext))
		{
			std::cerr << "ERROR: Failed to make GL context current" << std::endl;
			return false;
		}

		return true;
	}

	bool LinuxOpenGLContext::swapBuffers()
	{
		glXSwapBuffers(_display, _window);
		return true;
	}

	bool LinuxOpenGLContext::createContext(int majorVersion, int minorVersion)
	{
		int fbConfigAttribs[] = {
			GLX_X_RENDERABLE,  True,
			GLX_DRAWABLE_TYPE, GLX_WINDOW_BIT,
			GLX_RENDER_TYPE,   GLX_RGBA_BIT,
			GLX_X_VISUAL_TYPE, GLX_TRUE_COLOR,
			GLX_RED_SIZE,     8,
			GLX_GREEN_SIZE,   8,
			GLX_BLUE_SIZE,    8,
			GLX_ALPHA_SIZE,    8,
			GLX_DEPTH_SIZE,    24,
			GLX_STENCIL_SIZE, 8,
			GLX_DOUBLEBUFFER,  True,
			None
		};

		int glxMajor, glxMinor;
		if (!glXQueryVersion(_display, &glxMajor, &glxMinor))
		{
			std::cerr << "ERROR: Failed to query GLX version" << std::endl;
			return false;
		}

		std::cout << "GLX version: " << glxMajor << "." << glxMinor << std::endl;

		if (glxMajor < 1 || (glxMajor == 1 && glxMinor < 3))
		{
			std::cerr << "ERROR: GLX version 1.3 or higher is required" << std::endl;
			return false;
		}

		int fbCount;
		GLXFBConfig* fbConfigs = glXChooseFBConfig(_display, DefaultScreen(_display), fbConfigAttribs, &fbCount);
		if (!fbConfigs || fbCount == 0)
		{
			std::cerr << "ERROR: Failed to get framebuffer config" << std::endl;
			return false;
		}

		GLXFBConfig fbConfig = fbConfigs[0];
		XFree(fbConfigs);

		int contextAttribs[] = {
			GLX_CONTEXT_MAJOR_VERSION_ARB, majorVersion,
			GLX_CONTEXT_MINOR_VERSION_ARB, minorVersion,
			GLX_CONTEXT_PROFILE_MASK_ARB,  GLX_CONTEXT_CORE_PROFILE_BIT_ARB,
			None
		};

		const char* glxExts = glXQueryExtensionsString(_display, DefaultScreen(_display));
		if (!strstr(glxExts, "GLX_ARB_create_context"))
		{
			std::cerr << "ERROR: GLX_ARB_create_context extension not found" << std::endl;
			return false;
		}

		typedef GLXContext(*glXCreateContextAttribsARBProc)(Display*, GLXFBConfig, GLXContext, Bool, const int*);
		auto glXCreateContextAttribsARB = (glXCreateContextAttribsARBProc)glXGetProcAddressARB((const GLubyte*)"glXCreateContextAttribsARB");

		if (!glXCreateContextAttribsARB)
		{
			std::cerr << "ERROR: Failed to get glXCreateContextAttribsARB address" << std::endl;
			return false;
		}

		_glContext = glXCreateContextAttribsARB(_display, fbConfig, nullptr, True, contextAttribs);
		if (!_glContext)
		{
			std::cerr << "ERROR: Failed to create modern OpenGL context" << std::endl;
			return false;
		}
		return true;
	}

	bool LinuxOpenGLContext::releaseContext()
	{
		if (_isInitialized)
		{
			glXMakeCurrent(_display, None, NULL);
			glXDestroyContext(_display, _glContext);
			_isInitialized = false;
			return true;
		}

		return false;
	}

	bool LinuxOpenGLContext::init()
	{
		if (!createContext(4, 5))
		{
			std::cerr << "ERROR: Failed to create OpenGL context" << std::endl;
			return false;
		}

		if (!makeCurrent())
		{
			std::cerr << "ERROR: Failed to make context current" << std::endl;
			return false;
		}

		if (!init_glad())
		{
			std::cout << "ERROR: Failed to initialize GLAD" << std::endl;
			return false;
		}

		return true;
	}

}