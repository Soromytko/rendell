#include <rendell/rendell.h>

#include "IContext.h"
#include "OpenGL/OpenGLSpecification.h"
#include "Specification.h"
#include "context_creation.h"

#include <memory>
#include <mutex>
#include <thread>

#include <rendell/DataType.h>
#include <rendell/rendell_static.h>

#include <RenderContextManager.h>
#include <Command.h>
#include <CommandBuffer.h>
#include <CommandExecutor.h>
#include <logging.h>
#include <DrawCallState.h>

#include <Backend/Factory.h>
#include <Backend/FragmentShader.h>
#include <Backend/IndexBuffer.h>
#include <Backend/ShaderProgram.h>
#include <Backend/Texture2D.h>
#include <Backend/Texture2DArray.h>
#include <Backend/Uniform.h>
#include <Backend/VertexArray.h>
#include <Backend/VertexBuffer.h>
#include <Backend/VertexShader.h>

#define TO_BYTES(v) reinterpret_cast<const uint8_t *>(&v)

// Static data
namespace rendell {
static const auto s_mainThreadId = std::this_thread::get_id();

static CommandBuffer s_prepareCommandBuffer;
static CommandBuffer s_runtimeCommandBuffer;

} // namespace rendell

// Implementation
namespace rendell {
static void readCmdType(CmdType &type) {
}

thread_local DrawCallState s_drawCallState;

void setIndexBuffer(IndexBufferId indexBufferId) {
    //s_drawCallState.indexBufferId = indexBufferId;
}

void setVertexBuffer(VertexBufferId vertexBufferId) {
}

void setVertexArrayBuffer(VertexArrayBufferId vertexArrayBufferId) {
}

void setShaderProgram(ShaderProgramId shaderProgramId) {
}

static std::mutex s_renderFrameMutex;
static std::mutex s_submitMutex;

void submit() {
}

class {
public:
    const std::vector<ThreadRenderer *> &get() const { return _threadRenderers; }

    void add(ThreadRenderer *threadRenderer) {
        auto it =
            std::find(_threadRenderers.begin(), _threadRenderers.begin() + _size, threadRenderer);
        if (it == _threadRenderers.begin() + _size) {
            _threadRenderers.insert(it, threadRenderer);
            _size++;
        }
    }

    void reset() { _size = 0; }

private:
    std::vector<ThreadRenderer *> _threadRenderers;
    size_t _size;

} static s_usedThreadRenderers;

static std::mutex s_threadRendererMutex;

RenderContext *startThreadRender() {
    std::lock_guard(s_threadRendererMutex);

    RenderContext *renderContext = getRenderContext();
    return renderContext;
}

void endThreadRender(RenderContext *renderContext) {
    assert(renderContext);
    std::lock_guard(s_threadRendererMutex);

    CommandBufferSharedPtr prepareCommandBuffer = RenderContextManager::getAndSwap(renderContext);


    s_usedThreadRenderers.add(threadRenderer);
}

void prepare() {
    std::lock_guard<std::mutex> lock(s_renderFrameMutex);

    if (s_prepareCommandBuffer.getSize() == 0) {
        return;
    }

    while (true) {
        CmdType type;
        if (!readCmdType(s_prepareCommandBuffer, type)) {
            return;
        }
        switch (type) {
        case CmdType::createIndexBufferCmdType: {
            CreateIndexBufferCmdData cmdData;
            readCmdData(s_prepareCommandBuffer, cmdData);
            IndexBufferSharedPtr indexBuffer = getFactory()->createIndexBuffer(cmdData.data);
            s_indexBufferManager.setImpl(cmdData.id, indexBuffer);
            cmdData.data.release();
        } break;
        case CmdType::createVertexBufferCmdType: {
            CreateVertexBufferCmdData cmdData;
            readCmdData(s_prepareCommandBuffer, cmdData);
            VertexBufferSharedPtr vertexBuffer = getFactory()->createVertexBuffer(cmdData.data);
            s_vertexBufferManager.setImpl(cmdData.id, vertexBuffer);
            cmdData.data.release();

        } break;
        case CmdType::createVertexArrayBufferCmdType: {
            CreateVertexArrayBufferCmdData cmdData;
            readCmdData(s_prepareCommandBuffer, cmdData);

            // IndexBuffer
            IndexBufferSharedPtr indexBuffer = s_indexBufferManager.getImpl(cmdData.indexBufferId);

            // VertexBuffer
            std::vector<VertexBufferSharedPtr> vertexBuffers;
            vertexBuffers.reserve(cmdData.vertexBuffers.size);
            for (size_t i = 0; i < cmdData.vertexBuffers.size; i++) {
                const VertexBufferSharedPtr &vertexBuffer =
                    s_vertexBufferManager.getImpl(cmdData.vertexBuffers.data[i]);
                vertexBuffers.push_back(vertexBuffer);
            }

            VertexArraySharedPtr vertexArray =
                getFactory()->createVertexArrayBuffer(indexBuffer, vertexBuffers);
            s_vertexArrayBufferManager.setImpl(cmdData.id, vertexArray);

            cmdData.vertexBuffers.release();
        } break;
        case CmdType::createTexture2DCmdType: {
            CreateTexture2DCmdData cmdData;
            readCmdData(s_prepareCommandBuffer, cmdData);
            Texture2DSharedPtr texture2D = getFactory()->createTexture2D(
                cmdData.width, cmdData.height, cmdData.format, cmdData.data);
            s_texture2DManager.setImpl(cmdData.id, texture2D);

            cmdData.data.release();
        } break;
        case CmdType::createTexture2DArrayCmdType: {
            CreateTexture2DArrayCmdData cmdData;
            readCmdData(s_prepareCommandBuffer, cmdData);
            Texture2DArraySharedPtr texture2DArray = getFactory()->createTexture2DArray(
                cmdData.width, cmdData.height, cmdData.count, cmdData.format, cmdData.data);
            s_texture2DArrayManager.setImpl(cmdData.id, texture2DArray);

            cmdData.data.release();
        } break;
        case CmdType::createUniformBufferCmdType: {

        } break;
        case CmdType::createVertexShaderCmdType: {
            CreateVertexShaderCmdData cmdData;
            readCmdData(s_prepareCommandBuffer, cmdData);
            VertexShaderSharedPtr vertexShader = getFactory()->createVertexShader(cmdData.src);
            s_vertexShaderManager.setImpl(cmdData.id, vertexShader);

            cmdData.src.release();
        } break;
        case CmdType::createFragmentShaderCmdType: {

        } break;
        case CmdType::createShaderProgramCmdType: {
            CreateShaderProgramCmdData cmdData;
            readCmdData(s_prepareCommandBuffer, cmdData);
            VertexShaderSharedPtr vertexShader =
                s_vertexShaderManager.getImpl(cmdData.vertexShaderId);
            FragmentShaderSharedPtr fragmentShader =
                s_fragmentShaderManager.getImpl(cmdData.fragmentShaderId);
            ShaderProgramSharedPtr shaderProgram =
                getFactory()->createShaderProgram(vertexShader, fragmentShader);
            s_shaderProgramManager.setImpl(cmdData.id, shaderProgram);
        } break;
        case CmdType::createUniformCmdType: {

        } break;
        }
    }
}

void renderFrame(NativeViewId nativeFrameId) {
    {
        s_rendererMutex;

        returnThreadRenderer(threadRenderer);
    }

    prepare();

    return getContext(nativeView)->draw();
}

} // namespace rendell

namespace rendell {
static Specification *s_specification = nullptr;
static std::unordered_map<context_id, IContextSharedPtr> s_contexts;
static IContextSharedPtr s_currentContext = nullptr;

static context_id generate_context_id() {
    static size_t counter;
    return ++counter;
}

void setClearBits(uint32_t clearBits) {
    s_specification->setClearBits(clearBits);
}

void clear() {
    s_specification->clear();
}

void clearColor(float r, float g, float b, float a) {
    s_specification->clearColor(r, g, b, a);
}

void setViewport(int x, int y, int width, int height, int windowWidth, int windowHeight) {
    s_specification->setViewport(x, y, width, height, windowWidth, windowHeight);
}

void setPixelUnpackAlignment(int param) {
    s_specification->setPixelUnpackAlignment(param);
}

void startScissors(int x, int y, int width, int height) {
    s_specification->startScissors(x, y, width, height);
}

void endScissors() {
    s_specification->endScissors();
}

void finish() {
    glFinish();
}

void drawLineArrays(uint32_t firstIndex, uint32_t length) {
    s_specification->drawLineArrays(firstIndex, length);
}

void drawLineArraysInstanced(uint32_t firstIndex, uint32_t length, uint32_t instanceCount) {
    s_specification->drawLineArraysInstanced(firstIndex, length, instanceCount);
}

void drawLineElements(uint32_t primitiveCount) {
    s_specification->drawLineElements(primitiveCount);
}

void drawLineElementsInstanced(uint32_t primitiveCount, uint32_t instanceCount) {
    s_specification->drawLineElementsInstanced(primitiveCount, instanceCount);
}

void drawTriangleArrays(uint32_t firstIndex, uint32_t length) {
    s_specification->drawTriangleArrays(firstIndex, length);
}

void drawTriangleArraysInstanced(uint32_t firstIndex, uint32_t length, uint32_t instanceCount) {
    s_specification->drawTriangleArraysInstanced(firstIndex, length, instanceCount);
}

void drawTriangleElements(uint32_t primitiveCount) {
    s_specification->drawTriangleElements(primitiveCount);
}

void drawTriangleElementsInstanced(uint32_t primitiveCount, uint32_t instanceCount) {
    s_specification->drawTriangleElementsInstanced(primitiveCount, instanceCount);
}

void drawTriangleStripArrays(uint32_t firstIndex, uint32_t length) {
    s_specification->drawTriangleStripArrays(firstIndex, length);
}

void drawTriangleStripArraysInstanced(uint32_t firstIndex, uint32_t length,
                                      uint32_t instanceCount) {
    s_specification->drawTriangleStripArraysInstanced(firstIndex, length, instanceCount);
}

void drawTriangleStripElements(uint32_t primitiveCount) {
    s_specification->drawTriangleStripElements(primitiveCount);
}

void drawTriangleStripElementsInstanced(uint32_t primitiveCount, uint32_t instanceCount) {
    s_specification->drawTriangleStripElementsInstanced(primitiveCount, instanceCount);
}

} // namespace rendell
