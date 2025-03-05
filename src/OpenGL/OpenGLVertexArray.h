#include "../VertexArray.h"
#include <glad/glad.h>

namespace rendell
{
	class OpenGLVertexArray final : public VertexArray
	{
	public:
		OpenGLVertexArray();
		OpenGLVertexArray(IndexBufferSharedPtr indexBuffer, std::initializer_list<VertexBufferSharedPtr> buffers);
		~OpenGLVertexArray();
		void bind() const override;
		void unbind() const override;
		void setIndexBuffer(IndexBufferSharedPtr indexBuffer) override;
		void addVertexBuffer(VertexBufferSharedPtr vertexBuffer) override;

	private:
		GLuint _vertexArrayId{};
	};

	DECLARE_SHARED_PTR_FACTORY(OpenGLVertexArray)
	
}