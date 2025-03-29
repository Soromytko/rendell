#pragma once
#include <rendell/VertexBuffer.h>
#include <glad/glad.h>

namespace rendell
{
	class OpenGLVertexBuffer final : public VertexBuffer
	{
		//friend class VertexBuffer;
	public:
		OpenGLVertexBuffer(std::vector<float>&& data);
		~OpenGLVertexBuffer();
	public:
		void bind() const override;
		void unbind() const override;
	private:
		GLuint _bufferId{};
	};

	RENDELL_DECLARE_SHARED_PTR_FACTORY(OpenGLVertexBuffer)
}