#include <RenderPipelineStorage.h>

#include <OpenGL/OpenGLRenderPipeline.h>
#include <OpenGL/OpenGLRenderPipelineSync.h>
#include <logging.h>

namespace rendell {
RenderPipelineStorage *s_renderPipelineStorage = nullptr;

void RenderPipelineStorage::init() {
    assert(!s_renderPipelineStorage);
    s_renderPipelineStorage = new RenderPipelineStorage();
}

void RenderPipelineStorage::release() {
    assert(s_renderPipelineStorage);
    delete s_renderPipelineStorage;
}

RenderPipelineStorage *RenderPipelineStorage::getInstance() {
    assert(s_renderPipelineStorage);
    return s_renderPipelineStorage;
}

static std::unique_ptr<RenderPipeline> createSpecificRenderPipelineSync(SpecificationAPI api,
                                                                        NativeView nativeView) {
    switch (api) {
    case SpecificationAPI::OpenGL45: {
        return std::make_unique<OpenGLRenderPipelineSync>(nativeView);
    }
    case SpecificationAPI::Vulkan: {
        return nullptr;
    }
    case SpecificationAPI::DirectX12: {
        return nullptr;
    }
    default: {
        RENDELL_CRITICAL("Unknown graphics API!");
        assert(false);
    }
    }
    return nullptr;
}

static std::unique_ptr<RenderPipeline> createSpecificRenderPipeline(SpecificationAPI api,
                                                                    NativeView nativeView) {
    switch (api) {
    case SpecificationAPI::OpenGL45: {
        return std::make_unique<OpenGLRenderPipeline>(nativeView);
    }
    case SpecificationAPI::Vulkan: {
        return nullptr;
    }
    case SpecificationAPI::DirectX12: {
        return nullptr;
    }
    default: {
        RENDELL_CRITICAL("Unknown graphics API!");
        assert(false);
    }
    }
    return nullptr;
}

static NativeViewId generateNativeViewId() {
    static NativeViewId counter = 1;
    return counter++;
}

const std::vector<NativeViewId> &RenderPipelineStorage::getNativeViewIds() const {
    return _nativeViewIds;
}

NativeViewId RenderPipelineStorage::createRenderPipeline(SpecificationAPI api,
                                                         NativeView nativeView,
                                                         bool useSeparateRenderThread) {
    std::unique_ptr<RenderPipeline> renderPipeline =
        useSeparateRenderThread ? createSpecificRenderPipeline(api, nativeView)
                                : createSpecificRenderPipelineSync(api, nativeView);
    assert(renderPipeline);
    if (!renderPipeline->isInitialized()) {
        return 0;
    }
    const IContext *context = renderPipeline->getContext();
    assert(context);
    RENDELL_INFO("The rendering context has been created: {}", context->getName());

    NativeViewId nativeViewId = generateNativeViewId();

    RenderPipeline *rawRenderPipelinePtr = renderPipeline.get();

    _nativeViewIds.push_back(nativeViewId);
    _renderPipelines.push_back(std::move(renderPipeline));

    rawRenderPipelinePtr->run();

    return nativeViewId;
}

void RenderPipelineStorage::releaseRenderPipeline(NativeViewId nativeViewId) {
    assert(nativeViewId != InvalidNativeViewId);
    const size_t index = static_cast<size_t>(nativeViewId - 1);
    assert(_nativeViewIds.size() == _renderPipelines.size());
    assert(index < _renderPipelines.size());
    _nativeViewIds.erase(_nativeViewIds.begin() + index);
    _renderPipelines.erase(_renderPipelines.begin() + index);
}

RenderPipeline *RenderPipelineStorage::getRenderPipeline(NativeViewId nativeViewId) const {
    assert(nativeViewId != InvalidNativeViewId);
    const size_t index = static_cast<size_t>(nativeViewId - 1);
    if (index >= _renderPipelines.size()) {
        // TODO: warning!
        return nullptr;
    }
    return _renderPipelines[index].get();
}

} // namespace rendell