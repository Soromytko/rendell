#include "OpenGL/OpenGLFactory.h"
#include <Backend/Factory.h>
#include <cassert>

namespace rendell {
static FactoryUniquePtr s_factory{nullptr};

Factory *getFactory() {
    return s_factory.get();
}

void initOpenGLFactory() {
    s_factory = makeOpenGLFactory();
}

void initVulkanFactory() {
    assert(false);
}

void initDirectX12Factory() {
    assert(false);
}

void releaseFactory() {
    s_factory.release();
}
} // namespace rendell