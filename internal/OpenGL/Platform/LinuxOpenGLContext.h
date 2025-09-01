#pragma once
#include <IContext.h>
#include <raii.h>
#include <rendell/init_types.h>

#include <string>

// Make sure glad.h is included before any other OpenGL headers.
#include <glad/glad.h>

#include <GL/glx.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>

namespace rendell {
class LinuxOpenGLContext final : public IContext {
public:
    LinuxOpenGLContext(const NativeView &nativeView);
    ~LinuxOpenGLContext();

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

    Display *_display{nullptr};
    Window _window{0};
    GLXContext _glContext{nullptr};
    XVisualInfo *_visualInfo{nullptr};
    bool _isInitialized{false};
};

RENDELL_USE_RAII_FACTORY(LinuxOpenGLContext)
} // namespace rendell
