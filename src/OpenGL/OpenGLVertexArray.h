#include <Backend/VertexArray.h>
#include <glad/glad.h>

namespace rendell {
class OpenGLVertexArray final : public VertexArray {
public:
    OpenGLVertexArray(const IndexBufferSharedPtr &indexBuffer,
                      const std::vector<VertexBufferSharedPtr> &vertexBuffers);
    ~OpenGLVertexArray();

    void bind() const override;
    void unbind() const override;
    void setIndexBuffer(IndexBufferSharedPtr indexBuffer) override;
    void addVertexBuffer(VertexBufferSharedPtr vertexBuffer) override;

private:
    GLuint _vertexArrayId{};
};

RENDELL_USE_RAII_FACTORY(OpenGLVertexArray)

} // namespace rendell