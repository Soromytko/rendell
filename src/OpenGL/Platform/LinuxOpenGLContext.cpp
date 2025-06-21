#include "LinuxOpenGLContext.h"
#include <logging.h>
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
			RENDELL_ERROR("Initer::nativeWindowHandle field is nullptr");
			return;
		}
		_window = static_cast<Window>(reinterpret_cast<size_t>(initer.nativeWindowHandle));

		if (initer.x11Display == nullptr)
		{
			RENDELL_ERROR("Initer::x11Display field is nullptr");
			return;
		}
		_display = reinterpret_cast<Display*>(initer.x11Display);

		_isInitialized = init();
		if (!_isInitialized)
		{
			RENDELL_ERROR("Failed to initialize X11 OpenGL context");
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
			RENDELL_ERROR("Failed to make GL context current");
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
			RENDELL_ERROR("Failed to query GLX version");
			return false;
		}

		RENDELL_INFO("GLX version: {}.{}", glxMajor, glxMinor);

		if (glxMajor < 1 || (glxMajor == 1 && glxMinor < 3))
		{
			RENDELL_ERROR("ERROR: GLX version 1.3 or higher is required");
			return false;
		}

		int fbCount;
		GLXFBConfig* fbConfigs = glXChooseFBConfig(_display, DefaultScreen(_display), fbConfigAttribs, &fbCount);
		if (!fbConfigs || fbCount == 0)
		{
			RENDELL_ERROR("Failed to get framebuffer config");
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
			RENDELL_ERROR("GLX_ARB_create_context extension not found");
			return false;
		}

		typedef GLXContext(*glXCreateContextAttribsARBProc)(Display*, GLXFBConfig, GLXContext, Bool, const int*);
		auto glXCreateContextAttribsARB = (glXCreateContextAttribsARBProc)glXGetProcAddressARB((const GLubyte*)"glXCreateContextAttribsARB");

		if (!glXCreateContextAttribsARB)
		{
			RENDELL_ERROR("ERROR: Failed to get glXCreateContextAttribsARB address");
			return false;
		}

		_glContext = glXCreateContextAttribsARB(_display, fbConfig, nullptr, True, contextAttribs);
		if (!_glContext)
		{
			RENDELL_ERROR("Failed to create modern OpenGL context");
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
			RENDELL_ERROR("Failed to create OpenGL context");
			return false;
		}

		if (!makeCurrent())
		{
			RENDELL_ERROR("Failed to make context current");
			return false;
		}

		if (!init_glad())
		{
			RENDELL_ERROR("Failed to initialize GLAD");
			return false;
		}

		return true;
	}

}