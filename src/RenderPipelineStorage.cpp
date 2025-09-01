#include <RenderPipelineStorage.h>

#include <OpenGL/OpenGLRenderPipeline.h>
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

static RenderPipelineSharedPtr createSpecificRenderPipeline(SpecificationAPI api,
                                                            NativeView nativeView) {
    switch (api) {
    case SpecificationAPI::OpenGL45: {
        return makeOpenGLRenderPipeline(nativeView);
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
                                                         NativeView nativeView) {
    RenderPipelineSharedPtr renderPipeline = createSpecificRenderPipeline(api, nativeView);
    assert(renderPipeline);
    if (!renderPipeline->isInitialized()) {
        return 0;
    }
    const IContext *context = renderPipeline->getContext();
    assert(context);
    RENDELL_INFO("The rendering context has been created: {}", context->getName());

    NativeViewId nativeViewId = generateNativeViewId();

    _nativeViewIds.push_back(nativeViewId);
    _renderPipelines.push_back(renderPipeline);

    renderPipeline->run();

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

RenderPipelineSharedPtr RenderPipelineStorage::getRenderPipeline(NativeViewId nativeViewId) const {
    assert(nativeViewId != InvalidNativeViewId);
    const size_t index = static_cast<size_t>(nativeViewId - 1);
    if (index >= _renderPipelines.size()) {
        // TODO: warning!
        return nullptr;
    }
    return _renderPipelines[index];
}

} // namespace rendell