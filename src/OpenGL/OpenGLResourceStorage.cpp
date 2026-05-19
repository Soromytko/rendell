#include <OpenGL/OpenGLResourceStorage.h>

#include <cassert>
#include <unordered_map>

namespace rendell {
static OpenGLResourceStorage<std::unique_ptr<OpenGLIndexBuffer>> s_indexBufferStorage;
static OpenGLResourceStorage<std::unique_ptr<OpenGLVertexBuffer>> s_vertexBufferStorage;
static OpenGLResourceStorage<std::unique_ptr<OpenGLVertexArray>> s_vertexArrayBufferStorage;
static OpenGLResourceStorage<std::unique_ptr<OpenGLUniformBuffer>> s_uniformBufferStorage;
static OpenGLResourceStorage<std::unique_ptr<OpenGLShaderBuffer>> s_shaderBufferStorage;
static OpenGLResourceStorage<std::unique_ptr<OpenGLTexture2D>> s_texture2DStorage;
static OpenGLResourceStorage<std::unique_ptr<OpenGLTexture2DArray>> s_texture2DArrayStorage;
static OpenGLResourceStorage<std::unique_ptr<OpenGLVertexShader>> s_vertexShaderStorage;
static OpenGLResourceStorage<std::unique_ptr<OpenGLFragmentShader>> s_fragmentShaderStorage;
static OpenGLResourceStorage<std::unique_ptr<OpenGLShaderProgram>> s_shaderProgramStorage;

static std::unordered_map<size_t, std::string> s_uniformNames;
} // namespace rendell

namespace rendell {
OpenGLResourceStorage<std::unique_ptr<OpenGLIndexBuffer>> &getIndexBufferStorage() {
    return s_indexBufferStorage;
}

OpenGLResourceStorage<std::unique_ptr<OpenGLVertexBuffer>> &getVertexBufferStorage() {
    return s_vertexBufferStorage;
}

OpenGLResourceStorage<std::unique_ptr<OpenGLVertexArray>> &getVertexArrayBufferStorage() {
    return s_vertexArrayBufferStorage;
}

OpenGLResourceStorage<std::unique_ptr<OpenGLUniformBuffer>> &getUniformBufferStorage() {
    return s_uniformBufferStorage;
}

OpenGLResourceStorage<std::unique_ptr<OpenGLShaderBuffer>> &getShaderBufferStorage() {
    return s_shaderBufferStorage;
}

OpenGLResourceStorage<std::unique_ptr<OpenGLTexture2D>> &getTexture2DStorage() {
    return s_texture2DStorage;
}

OpenGLResourceStorage<std::unique_ptr<OpenGLTexture2DArray>> &getTexture2DArrayStorage() {
    return s_texture2DArrayStorage;
}

OpenGLResourceStorage<std::unique_ptr<OpenGLVertexShader>> &getVertexShaderStorage() {
    return s_vertexShaderStorage;
}

OpenGLResourceStorage<std::unique_ptr<OpenGLFragmentShader>> &getFragmentShaderStorage() {
    return s_fragmentShaderStorage;
}

OpenGLResourceStorage<std::unique_ptr<OpenGLShaderProgram>> &getShaderProgramStorage() {
    return s_shaderProgramStorage;
}

static size_t generateKey() {
    static size_t counter = 0;
    return ++counter;
}

void storeUniformName(size_t key, std::string &&name) {
    s_uniformNames[key] = std::move(name);
}

const std::string &getUniformName(size_t key) {
    auto it = s_uniformNames.find(key);
    assert(it != s_uniformNames.end());
    return it->second;
}

void removeUniformName(size_t key) {
    auto it = s_uniformNames.find(key);
    assert(it != s_uniformNames.end());
    s_uniformNames.erase(it);
}

void releaseOpenGLResourceStorages() {
    s_indexBufferStorage.clear();
    s_vertexBufferStorage.clear();
    s_vertexArrayBufferStorage.clear();
    s_uniformBufferStorage.clear();
    s_shaderBufferStorage.clear();
    s_texture2DStorage.clear();
    s_texture2DArrayStorage.clear();
    s_vertexShaderStorage.clear();
    s_fragmentShaderStorage.clear();
    s_shaderProgramStorage.clear();
}

} // namespace rendell