#pragma once
#include <glad/glad.h>
#include <rendell/UniformBuffer.h>

namespace rendell
{
	class OpenGLUniformBuffer final : public UniformBuffer
	{
	public:
		OpenGLUniformBuffer(const void* data, size_t size);

		void bind(uint32_t binding = 0) const override;
		void unbind() const override;
		void setSubData(const void* data, size_t size, size_t offset = 0) const override;

	private:
		mutable uint32_t _binding{ 0 };
		GLuint _id;
	};

	RENDELL_DECLARE_SHARED_PTR_FACTORY(OpenGLUniformBuffer)
}