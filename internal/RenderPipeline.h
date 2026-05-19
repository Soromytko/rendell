#pragma once
#include "IContext.h"
#include <rendell/RenderCommandBuffer.h>
#include <rendell/ResourceCommandBuffer.h>

#include <cassert>
#include <functional>

namespace rendell {
struct ReleasedResourceIds;

class RenderPipeline {
public:
    struct Callbacks {
        using ReturnResourceCommandBuffer = std::function<void(ResourceCommandBuffer *buffer)>;
        using ReturnRenderCommandBuffer = std::function<void(RenderCommandBuffer *buffer)>;
        ReturnResourceCommandBuffer returnResourceCommandBuffer;
        ReturnRenderCommandBuffer returnRenderCommandBuffer;

        inline bool isValid() const noexcept {
            return returnResourceCommandBuffer != nullptr && returnRenderCommandBuffer != nullptr;
        }
    };

    RenderPipeline(Callbacks callback)
        : _callbacks(callback) {
        assert(_callbacks.isValid());
    }

    virtual ~RenderPipeline() = default;

    virtual bool isInitialized() const = 0;
    virtual const IContext *getContext() const = 0;
    virtual const ReleasedResourceIds &getReleasedResourceIds() const = 0;

    virtual void run() = 0;

    virtual void submitResourceContext(ResourceCommandBuffer *buffer) = 0;
    virtual void submitRenderContext(RenderCommandBuffer *buffer) = 0;

    virtual void waitAndRender() = 0;

protected:
    Callbacks _callbacks;
};
} // namespace rendell