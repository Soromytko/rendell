#pragma once
#include <OpenGL/OpenGLFragmentShader.h>
#include <OpenGL/OpenGLIndexBuffer.h>
#include <OpenGL/OpenGLShaderBuffer.h>
#include <OpenGL/OpenGLShaderProgram.h>
#include <OpenGL/OpenGLTexture2D.h>
#include <OpenGL/OpenGLTexture2DArray.h>
#include <OpenGL/OpenGLUniformBuffer.h>
#include <OpenGL/OpenGLVertexArray.h>
#include <OpenGL/OpenGLVertexBuffer.h>
#include <OpenGL/OpenGLVertexBufferLayout.h>
#include <OpenGL/OpenGLVertexShader.h>

#include <cassert>
#include <vector>

namespace rendell {
template <typename T> class OpenGLResourceStorage final {
public:
    const T &find(size_t index) const {
        assert(index < _storage.size());
        return _storage[index];
    }

    void store(size_t index, T value) {
        if (_storage.size() <= index) {
            _storage.resize(index + 1);
        }
        _storage[index] = std::move(value);
    }

    void destroy(size_t index) {
        assert(index < _storage.size());
        _storage[index] = nullptr;
    }

    void clear() { _storage.clear(); }

private:
    std::vector<T> _storage;
};

OpenGLResourceStorage<OpenGLIndexBufferUniquePtr> &getIndexBufferStorage();
OpenGLResourceStorage<OpenGLVertexBufferUniquePtr> &getVertexBufferStorage();
OpenGLResourceStorage<OpenGLVertexArrayUniquePtr> &getVertexArrayBufferStorage();
OpenGLResourceStorage<OpenGLUniformBufferUniquePtr> &getUniformBufferStorage();
OpenGLResourceStorage<OpenGLShaderBufferUniquePtr> &getShaderBufferStorage();
OpenGLResourceStorage<OpenGLTexture2DUniquePtr> &getTexture2DStorage();
OpenGLResourceStorage<OpenGLTexture2DArrayUniquePtr> &getTexture2DArrayStorage();
OpenGLResourceStorage<OpenGLVertexShaderSharedPtr> &getVertexShaderStorage();
OpenGLResourceStorage<OpenGLFragmentShaderSharedPtr> &getFragmentShaderStorage();
OpenGLResourceStorage<OpenGLShaderProgramUniquePtr> &getShaderProgramStorage();

void storeUniformName(size_t key, std::string &&name);
const std::string &getUniformName(size_t key);
void removeUniformName(size_t key);

void releaseOpenGLResourceStorages();
} // namespace rendell