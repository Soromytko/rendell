#pragma once
#include <memory>
#include <string>

namespace rendell {
class IContext {
public:
    IContext() = default;
    virtual ~IContext() = default;

    virtual const std::string &getName() const = 0;
    virtual bool isInitialized() const = 0;
    virtual bool makeCurrent() = 0;
    virtual bool makeUncurrent() = 0;
    virtual bool swapBuffers() = 0;
};
} // namespace rendell