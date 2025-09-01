#pragma once
#include "IContext.h"
#include "RenderContext.h"
#include "ResourceContext.h"
#include "raii.h"

#include <functional>

namespace rendell {
class RenderPipeline {
public:
    using ResourceContextReleasedCallback = std::function<void(ResourceContext *resourceContext)>;
    using RenderContextReleasedCallback = std::function<void(RenderContext *renderContext)>;

    RenderPipeline() = default;
    virtual ~RenderPipeline() = default;

    inline void setResourceContextReleasedCallback(ResourceContextReleasedCallback callback) {
        _resourceContextReleasedCallback = callback;
    }

    inline void setRenderContextReleasedCallback(RenderContextReleasedCallback callback) {
        _renderContextReleasedCallback = callback;
    }

    virtual bool isInitialized() const = 0;
    virtual const IContext *getContext() const = 0;

    virtual void run() = 0;

    virtual void submitResourceContext(ResourceContext *resourceContext) = 0;
    virtual void submitRenderContext(RenderContext *renderContext) = 0;

    virtual void waitAndRender() = 0;

protected:
    ResourceContextReleasedCallback _resourceContextReleasedCallback;
    RenderContextReleasedCallback _renderContextReleasedCallback;
};

RENDELL_USE_RAII(RenderPipeline)
} // namespace rendell