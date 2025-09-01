#pragma once
#include <IContext.h>
#include <raii.h>
#include <rendell/init_types.h>

#include <Windows.h>

namespace rendell {
class WindowsOpenGLContext final : public IContext {
public:
    WindowsOpenGLContext(const NativeView &nativeView);
    ~WindowsOpenGLContext();

    const std::string &getName() const override;
    bool isInitialized() const override;
    bool makeCurrent() override;
    bool makeUncurrent() override;
    bool swapBuffers() override;

private:
    bool createContext(int majorVersion, int minorVersion);
    bool releaseContext();
    bool init();

    std::string _name{};

    HWND _hwnd = NULL;
    PIXELFORMATDESCRIPTOR _pfd{};
    HDC _hdc = NULL;
    HGLRC _hglrc = NULL;

    bool _isInitialized{false};
};

RENDELL_USE_RAII_FACTORY(WindowsOpenGLContext)
} // namespace rendell
