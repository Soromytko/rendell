#include <Factory.h>
#include <rendell/rendell_static.h>

namespace rendell {
static Factory *s_currentFactory{nullptr};
} // namespace rendell

namespace rendell {
void setCurrentFactory(Factory *factory) {
    s_currentFactory = factory;
}

Factory *getCurrentFactory() {
    return s_currentFactory;
}

} // namespace rendell