#pragma once
#include <glad/glad.h>
#include <Backend/IndexBuffer.h>

namespace rendell {
class OpenGLIndexBuffer final : public rendell::IndexBuffer {
public:
    OpenGLIndexBuffer(ArrayRef<uint32_t> indices);
    ~OpenGLIndexBuffer();

    void bind() const override;
    void unbind() const override;

private:
    GLuint _bufferId{};
};

RENDELL_USE_RAII_FACTORY(OpenGLIndexBuffer)
} // namespace rendell
