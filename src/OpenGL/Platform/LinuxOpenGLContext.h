#pragma once
#include "../../IContext.h"
#include <GL/glx.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <rendell/private/defines.h>

namespace rendell {
class LinuxOpenGLContext final : public IContext {
public:
    LinuxOpenGLContext(const Initer &initer);
    ~LinuxOpenGLContext();

    Specification *getSpecification() const override;
    std::string getName() const override;
    bool isInitialized() const override;
    bool makeCurrent() override;
    bool swapBuffers() override;

private:
    bool createContext(int majorVersion, int minorVersion);
    bool releaseContext();
    bool init();

    Display *_display{nullptr};
    Window _window{0};
    GLXContext _glContext{nullptr};
    XVisualInfo *_visualInfo{nullptr};
    bool _isInitialized{false};
};

RENDELL_USE_RAII_FACTORY(LinuxOpenGLContext)
} // namespace rendell
