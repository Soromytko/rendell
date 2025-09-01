#pragma once
#include <glad/glad.h>
#include <rendell/DataType.h>
#include <rendell/oop/raii.h>

namespace rendell {
class OpenGLIndexBuffer final {
public:
    OpenGLIndexBuffer(const index_t *data, size_t size, bool isDynamic = false);
    ~OpenGLIndexBuffer();

    inline size_t getCount() const { return _count; };

    void bind() const;
    void unbind() const;

    void setSubData(const index_t *data, size_t size, size_t offset = 0);

private:
    size_t _count;
    GLuint _bufferId{};
};

RENDELL_USE_RAII_FACTORY(OpenGLIndexBuffer)
} // namespace rendell
