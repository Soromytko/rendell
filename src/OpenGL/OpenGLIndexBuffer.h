#pragma once
#include <rendell/IndexBuffer.h>
#include <glad/glad.h>

namespace rendell
{
	class OpenGLIndexBuffer : public rendell::IndexBuffer
	{
	public:
		OpenGLIndexBuffer(std::vector<uint32_t>&& indices);
		~OpenGLIndexBuffer();
		void bind() const override;
		void unbind()  const override;

	private:
		GLuint _bufferId{};
	};

	RENDELL_DECLARE_SHARED_PTR_FACTORY(OpenGLIndexBuffer)
}
