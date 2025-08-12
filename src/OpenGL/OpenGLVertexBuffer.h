#pragma once
#include <glad/glad.h>
#include <rendell/VertexBuffer.h>

namespace rendell {
class OpenGLVertexBuffer final : public VertexBuffer {
public:
    OpenGLVertexBuffer(std::vector<float> &&data);
    ~OpenGLVertexBuffer();

public:
    void bind() const override;
    void unbind() const override;

private:
    GLuint _bufferId{};
};

RENDELL_DECLARE_SHARED_PTR_FACTORY(OpenGLVertexBuffer)
} // namespace rendell