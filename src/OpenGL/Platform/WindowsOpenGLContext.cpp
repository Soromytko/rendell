#include <OpenGL/Platform/WindowsOpenGLContext.h>

#include "../glad_initialization.h"
#include <gl/GL.h>
#include <gl/GLU.h>
#include <gl/wglext.h>
#include <logging.h>

namespace rendell {
WindowsOpenGLContext::WindowsOpenGLContext(const NativeView &nativeView) {
    if (nativeView.nativeWindowHandle == nullptr) {
        RENDELL_ERROR("NativeView::nativeWindowHandle field is nullptr");
        return;
    }
    _hwnd = static_cast<HWND>(nativeView.nativeWindowHandle);

    _hdc = GetDC(_hwnd);
    if (_hdc == NULL) {
        RENDELL_ERROR("HDC of main HWND is NULL");
        return;
    }

    _isInitialized = init();
    if (!_isInitialized) {
        RENDELL_ERROR("Failed to initialize Windows OpenGL context");
        return;
    }

    _name = "OpenGL version: " + std::string(get_OpenGL_version());
}

WindowsOpenGLContext::~WindowsOpenGLContext() {
    if (_isInitialized) {
        releaseContext();
    }
}

const std::string &WindowsOpenGLContext::getName() const {
    return _name;
}

bool WindowsOpenGLContext::isInitialized() const {
    return _isInitialized;
}

bool WindowsOpenGLContext::makeCurrent() {
    if (!wglMakeCurrent(_hdc, _hglrc)) {
        RENDELL_ERROR("Failed to activate OpenGL rendering context");
        return false;
    }

    return true;
}

bool WindowsOpenGLContext::makeUncurrent() {
    return wglMakeCurrent(nullptr, nullptr);
}

bool WindowsOpenGLContext::swapBuffers() {
    return SwapBuffers(_hdc);
}

class WglHelper final {
public:
    WglHelper() {
        _hwnd =
            CreateWindowEx(0, "TMP_Window", "Temporary Window", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT,
                           CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, NULL, NULL);

        _hdc = GetDC(_hwnd);

        PIXELFORMATDESCRIPTOR pfd = {};
        pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
        pfd.nVersion = 1;
        pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
        pfd.iPixelType = PFD_TYPE_RGBA;
        pfd.cColorBits = 32;
        pfd.cDepthBits = 24;
        pfd.cStencilBits = 8;
        pfd.iLayerType = PFD_MAIN_PLANE;

        int format = ChoosePixelFormat(_hdc, &pfd);
        if (!SetPixelFormat(_hdc, format, &pfd)) {
            ReleaseDC(_hwnd, _hdc);
            DestroyWindow(_hwnd);
            return;
        }

        _glrc = wglCreateContext(_hdc);
        if (!_glrc) {
            ReleaseDC(_hwnd, _hdc);
            DestroyWindow(_hwnd);
            return;
        }

        if (!wglMakeCurrent(_hdc, _glrc)) {
            wglDeleteContext(_glrc);
            ReleaseDC(_hwnd, _hdc);
            DestroyWindow(_hwnd);
            return;
        }

        _wglChoosePixelFormatARB =
            (PFNWGLCHOOSEPIXELFORMATARBPROC)wglGetProcAddress("wglChoosePixelFormatARB");
        _wglCreateContextAttribsARB =
            (PFNWGLCREATECONTEXTATTRIBSARBPROC)wglGetProcAddress("wglCreateContextAttribsARB");

        _isSuccess = true;
    }

    ~WglHelper() {
        if (_isSuccess) {
            wglDeleteContext(_glrc);
            ReleaseDC(_hwnd, _hdc);
            DestroyWindow(_hwnd);
        }
    }

    bool isSuccess() const { return _isSuccess; }

    PFNWGLCHOOSEPIXELFORMATARBPROC getWglChoosePixelFormatARB() const {
        return _wglChoosePixelFormatARB;
    }

    PFNWGLCREATECONTEXTATTRIBSARBPROC getWglCreateContextAttribsARB() const {
        return _wglCreateContextAttribsARB;
    }

private:
    HWND _hwnd{};
    HDC _hdc{};
    HGLRC _glrc{};
    PFNWGLCHOOSEPIXELFORMATARBPROC _wglChoosePixelFormatARB{};
    PFNWGLCREATECONTEXTATTRIBSARBPROC _wglCreateContextAttribsARB{};
    bool _isSuccess{false};
};

bool WindowsOpenGLContext::createContext(int majorVersion, int minorVersion) {
    WglHelper wglHelper;
    if (!wglHelper.isSuccess()) {
        RENDELL_ERROR("Failed to create temporary OpenGL context");
        return false;
    }

    const auto wglChoosePixelFormatARB = wglHelper.getWglChoosePixelFormatARB();
    if (!wglChoosePixelFormatARB) {
        RENDELL_ERROR("wglChoosePixelFormatARB is not available");
        return false;
    }
    const auto wglCreateContextAttribsARB = wglHelper.getWglCreateContextAttribsARB();
    if (!wglCreateContextAttribsARB) {
        RENDELL_ERROR("wglCreateContextAttribsARB is not available");
        return false;
    }

    const int pixelAttribs[] = {
        WGL_DRAW_TO_WINDOW_ARB,
        GL_TRUE,
        WGL_SUPPORT_OPENGL_ARB,
        GL_TRUE,
        WGL_DOUBLE_BUFFER_ARB,
        GL_TRUE,
        WGL_PIXEL_TYPE_ARB,
        WGL_TYPE_RGBA_ARB,
        WGL_COLOR_BITS_ARB,
        32,
        WGL_DEPTH_BITS_ARB,
        24,
        WGL_STENCIL_BITS_ARB,
        8,
        0,
    };

    int pixelFormat;
    UINT numFormats;
    if (!wglChoosePixelFormatARB(_hdc, pixelAttribs, nullptr, 1, &pixelFormat, &numFormats) ||
        numFormats == 0) {
        RENDELL_ERROR("Failed to choose pixel format");
        return false;
    }

    int contextAttribs[] = {
        WGL_CONTEXT_MAJOR_VERSION_ARB,
        majorVersion,
        WGL_CONTEXT_MINOR_VERSION_ARB,
        minorVersion,
        WGL_CONTEXT_PROFILE_MASK_ARB,
        WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
#ifdef _DEBUG
        WGL_CONTEXT_FLAGS_ARB,
        WGL_CONTEXT_DEBUG_BIT_ARB,
#endif
        0,
    };

    PIXELFORMATDESCRIPTOR pfd;
    DescribePixelFormat(_hdc, pixelFormat, sizeof(pfd), &pfd);
    if (!SetPixelFormat(_hdc, pixelFormat, &pfd)) {
        ReleaseDC(_hwnd, _hdc);
        DestroyWindow(_hwnd);
        return false;
    }

    _hglrc = wglCreateContextAttribsARB(_hdc, nullptr, contextAttribs);
    return _hglrc != nullptr;
}

bool WindowsOpenGLContext::releaseContext() {
    if (_isInitialized) {
        wglMakeCurrent(nullptr, nullptr);

        if (_hglrc) {
            wglDeleteContext(_hglrc);
            _hglrc = nullptr;
        }

        if (_hdc) {
            ReleaseDC(_hwnd, _hdc);
            _hdc = nullptr;
        }

        _isInitialized = false;
        return true;
    }

    return false;
}

bool WindowsOpenGLContext::init() {
    if (!createContext(4, 5)) {
        RENDELL_ERROR("Failed to create OpenGL context");
        return false;
    }

    if (!makeCurrent()) {
        RENDELL_ERROR("Failed to make context current");
        return false;
    }

    if (!init_glad()) {
        RENDELL_ERROR("Failed to initialize GLAD");
        return false;
    }

    return true;
}

} // namespace rendell