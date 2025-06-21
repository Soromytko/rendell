#include "WindowsOpenGLContext.h"
#include <logging.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <gl/wglext.h>
#include "../OpenGLSpecification.h"
#include "../glad_initialization.h"

namespace rendell
{
	static OpenGLSpecification s_openGLSpecification{};

	WindowsOpenGLContext::WindowsOpenGLContext(const Initer& initer)
	{
		if (initer.nativeWindowHandle == nullptr)
		{
			RENDELL_ERROR("Initer::nativeWindowHandle field is nullptr");
			return;
		}
		_hwnd = static_cast<HWND>(initer.nativeWindowHandle);

		_hdc = GetDC(_hwnd);
		if (_hdc == NULL)
		{
			RENDELL_ERROR("HDC of main HWND is NULL");
			return;
		}

		_isInitialized = init();
		if (!_isInitialized)
		{
			RENDELL_ERROR("Failed to initialize Windows OpenGL context");
		}
	}

	WindowsOpenGLContext::~WindowsOpenGLContext()
	{
		if (_isInitialized)
		{
			releaseContext();
		}
	}

	Specification* WindowsOpenGLContext::getSpecification() const
	{
		return  &s_openGLSpecification;
	}

	std::string WindowsOpenGLContext::getName() const
	{
		return "OpenGL version: " + std::string(get_OpenGL_version());
	}

	bool WindowsOpenGLContext::isInitialized() const
	{
		return _isInitialized;
	}

	bool WindowsOpenGLContext::makeCurrent()
	{
		if (!wglMakeCurrent(_hdc, _hglrc))
		{
			RENDELL_ERROR("Failed to activate OpenGL rendering context");
			return false;
		}

		return true;
	}

	bool WindowsOpenGLContext::swapBuffers()
	{
		return SwapBuffers(_hdc);
	}

	static bool getFuncPointers(PFNWGLCHOOSEPIXELFORMATARBPROC& wglChoosePixelFormatARB, PFNWGLCREATECONTEXTATTRIBSARBPROC& wglCreateContextAttribsARB)
	{
		HWND hwnd = CreateWindowEx(
			0,
			"TMP_Window",
			"Temporary Window",
			WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
			NULL,
			NULL,
			NULL,
			NULL
		);

		HDC hdc = GetDC(hwnd);

		PIXELFORMATDESCRIPTOR pfd = {
			sizeof(PIXELFORMATDESCRIPTOR),
			1,
			PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
			PFD_TYPE_RGBA,
			32,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			24,
			8,
			0,
			PFD_MAIN_PLANE,
			0, 0, 0, 0
		};

		int format = ChoosePixelFormat(hdc, &pfd);
		if (!SetPixelFormat(hdc, format, &pfd))
		{
			ReleaseDC(hwnd, hdc);
			DestroyWindow(hwnd);
			return false;
		}

		HGLRC glrc = wglCreateContext(hdc);
		if (!glrc)
		{
			ReleaseDC(hwnd, hdc);
			DestroyWindow(hwnd);
			return false;
		}

		if (!wglMakeCurrent(hdc, glrc))
		{
			wglDeleteContext(glrc);
			ReleaseDC(hwnd, hdc);
			DestroyWindow(hwnd);
			return false;
		}

		wglChoosePixelFormatARB = (PFNWGLCHOOSEPIXELFORMATARBPROC)wglGetProcAddress("wglChoosePixelFormatARB");
		wglCreateContextAttribsARB = (PFNWGLCREATECONTEXTATTRIBSARBPROC)wglGetProcAddress("wglCreateContextAttribsARB");

		wglDeleteContext(glrc);
		ReleaseDC(hwnd, hdc);
		DestroyWindow(hwnd);

		return true;
	}

	bool WindowsOpenGLContext::createContext(int majorVersion, int minorVersion)
	{
		PFNWGLCHOOSEPIXELFORMATARBPROC wglChoosePixelFormatARB = nullptr;
		PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB = nullptr;

		if (!getFuncPointers(wglChoosePixelFormatARB, wglCreateContextAttribsARB))
		{
			RENDELL_ERROR("Failed to create temporary OpenGL context");
			return false;
		}

		if (!wglChoosePixelFormatARB)
		{
			RENDELL_ERROR("wglChoosePixelFormatARB is not available");
			return false;
		}

		if (!wglCreateContextAttribsARB)
		{
			RENDELL_ERROR("wglCreateContextAttribsARB is not available");
			return false;
		}

		const int pixelAttribs[] = {
			WGL_DRAW_TO_WINDOW_ARB, GL_TRUE,
			WGL_SUPPORT_OPENGL_ARB, GL_TRUE,
			WGL_DOUBLE_BUFFER_ARB, GL_TRUE,
			WGL_PIXEL_TYPE_ARB, WGL_TYPE_RGBA_ARB,
			WGL_COLOR_BITS_ARB, 32,
			WGL_DEPTH_BITS_ARB, 24,
			WGL_STENCIL_BITS_ARB, 8,
			0
		};

		int pixelFormat;
		UINT numFormats;
		if (!wglChoosePixelFormatARB(_hdc, pixelAttribs, nullptr, 1, &pixelFormat, &numFormats) || numFormats == 0)
		{
			RENDELL_ERROR("Failed to choose pixel format");
			return false;
		}

		int contextAttribs[] = {
			WGL_CONTEXT_MAJOR_VERSION_ARB, majorVersion,
			WGL_CONTEXT_MINOR_VERSION_ARB, minorVersion,
			WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
	#ifdef _DEBUG
			WGL_CONTEXT_FLAGS_ARB, WGL_CONTEXT_DEBUG_BIT_ARB,
	#endif
			0
		};

		_hglrc = wglCreateContextAttribsARB(_hdc, nullptr, contextAttribs);
		return _hglrc != nullptr;
	}

	bool WindowsOpenGLContext::releaseContext()
	{
		if (_isInitialized)
		{
			wglDeleteContext(_hglrc);
			ReleaseDC(_hwnd, _hdc);
			_isInitialized = false;
			return true;
		}

		return false;
	}

	bool WindowsOpenGLContext::init()
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