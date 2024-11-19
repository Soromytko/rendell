#include "../VertexArray.h"
#include <glad/glad.h>

namespace rendell
{
	class OpenGLVertexArray final : public VertexArray
	{
	public:
		OpenGLVertexArray();
		OpenGLVertexArray(std::initializer_list<VertexBuffer*> buffers);
		~OpenGLVertexArray();
		void bind() const override;
		void unbind() const override;
		void setIndexBuffer(IndexBuffer* indexBuffer) override;
		void addVertexBuffer(VertexBuffer* vertexBuffer) override;

	private:
		GLuint _vertexArrayId{};
	};
}