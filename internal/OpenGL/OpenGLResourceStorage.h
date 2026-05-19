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

OpenGLResourceStorage<std::unique_ptr<OpenGLIndexBuffer>> &getIndexBufferStorage();
OpenGLResourceStorage<std::unique_ptr<OpenGLVertexBuffer>> &getVertexBufferStorage();
OpenGLResourceStorage<std::unique_ptr<OpenGLVertexArray>> &getVertexArrayBufferStorage();
OpenGLResourceStorage<std::unique_ptr<OpenGLUniformBuffer>> &getUniformBufferStorage();
OpenGLResourceStorage<std::unique_ptr<OpenGLShaderBuffer>> &getShaderBufferStorage();
OpenGLResourceStorage<std::unique_ptr<OpenGLTexture2D>> &getTexture2DStorage();
OpenGLResourceStorage<std::unique_ptr<OpenGLTexture2DArray>> &getTexture2DArrayStorage();
OpenGLResourceStorage<std::unique_ptr<OpenGLVertexShader>> &getVertexShaderStorage();
OpenGLResourceStorage<std::unique_ptr<OpenGLFragmentShader>> &getFragmentShaderStorage();
OpenGLResourceStorage<std::unique_ptr<OpenGLShaderProgram>> &getShaderProgramStorage();

void storeUniformName(size_t key, std::string &&name);
const std::string &getUniformName(size_t key);
void removeUniformName(size_t key);

void releaseOpenGLResourceStorages();
} // namespace rendell