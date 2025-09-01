#pragma once
#include <memory>
#include <rendell/private/defines.h>
#include <string>

namespace rendell {
class Specification;
} // namespace rendell

namespace rendell {
class IContext {
public:
    IContext() = default;
    virtual ~IContext() = default;

    virtual Specification *getSpecification() const = 0;
    virtual std::string getName() const = 0;
    virtual bool isInitialized() const = 0;
    virtual bool makeCurrent() = 0;
    virtual bool swapBuffers() = 0;
};

RENDELL_USE_RAII(IContext)

} // namespace rendell