#pragma once
#include <rendell/RenderContext.h>

namespace rendell {
class RenderContextFactory final {
private:
    RenderContextFactory() = default;

public:
    ~RenderContextFactory() = default;

    RenderContext *createRenderContex() const;
}