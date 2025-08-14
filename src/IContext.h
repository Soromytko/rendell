#pragma once
#include "Specification.h"
#include <Factory.h>
#include <memory>
#include <rendell/private/defines.h>

namespace rendell {
class IContext {
protected:
    IContext() = default;

public:
    ~IContext() = default;

    virtual Specification *getSpecification() const = 0;
    virtual Factory *getFactory() const = 0;
    virtual std::string getName() const = 0;
    virtual bool isInitialized() const = 0;
    virtual bool makeCurrent() = 0;
    virtual bool swapBuffers() = 0;
};

RENDELL_USE_RAII(IContext)

} // namespace rendell