#include <OpenGL/OpenGLResourceStorage.h>

#include <cassert>
#include <unordered_map>

namespace rendell {
static OpenGLResourceStorage<OpenGLIndexBufferUniquePtr> s_indexBufferStorage;
static OpenGLResourceStorage<OpenGLVertexBufferUniquePtr> s_vertexBufferStorage;
static OpenGLResourceStorage<OpenGLVertexArrayUniquePtr> s_vertexArrayBufferStorage;
static OpenGLResourceStorage<OpenGLUniformBufferUniquePtr> s_uniformBufferStorage;
static OpenGLResourceStorage<OpenGLShaderBufferUniquePtr> s_shaderBufferStorage;
static OpenGLResourceStorage<OpenGLTexture2DUniquePtr> s_texture2DStorage;
static OpenGLResourceStorage<OpenGLTexture2DArrayUniquePtr> s_texture2DArrayStorage;
static OpenGLResourceStorage<OpenGLVertexShaderSharedPtr> s_vertexShaderStorage;
static OpenGLResourceStorage<OpenGLFragmentShaderSharedPtr> s_fragmentShaderStorage;
static OpenGLResourceStorage<OpenGLShaderProgramUniquePtr> s_shaderProgramStorage;

static std::unordered_map<size_t, std::string> s_uniformNames;
} // namespace rendell

namespace rendell {
OpenGLResourceStorage<OpenGLIndexBufferUniquePtr> &getIndexBufferStorage() {
    return s_indexBufferStorage;
}

OpenGLResourceStorage<OpenGLVertexBufferUniquePtr> &getVertexBufferStorage() {
    return s_vertexBufferStorage;
}

OpenGLResourceStorage<OpenGLVertexArrayUniquePtr> &getVertexArrayBufferStorage() {
    return s_vertexArrayBufferStorage;
}

OpenGLResourceStorage<OpenGLUniformBufferUniquePtr> &getUniformBufferStorage() {
    return s_uniformBufferStorage;
}

OpenGLResourceStorage<OpenGLShaderBufferUniquePtr> &getShaderBufferStorage() {
    return s_shaderBufferStorage;
}

OpenGLResourceStorage<OpenGLTexture2DUniquePtr> &getTexture2DStorage() {
    return s_texture2DStorage;
}

OpenGLResourceStorage<OpenGLTexture2DArrayUniquePtr> &getTexture2DArrayStorage() {
    return s_texture2DArrayStorage;
}

OpenGLResourceStorage<OpenGLVertexShaderSharedPtr> &getVertexShaderStorage() {
    return s_vertexShaderStorage;
}

OpenGLResourceStorage<OpenGLFragmentShaderSharedPtr> &getFragmentShaderStorage() {
    return s_fragmentShaderStorage;
}

OpenGLResourceStorage<OpenGLShaderProgramUniquePtr> &getShaderProgramStorage() {
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