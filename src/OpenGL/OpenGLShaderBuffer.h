#pragma once
#include <rendell/ShaderBuffer.h>
#include "OpenGLUtils.h"

namespace rendell
{
	class OpenGLShaderBuffer final : public ShaderBuffer
	{
	public:
		OpenGLShaderBuffer(const void* data, size_t size);
		~OpenGLShaderBuffer();

		void bind(uint32_t binding = 0) const override;
		void unbind() const override;

		void setSubData(const void* data, size_t size, size_t offset = 0) override;

	private:
		GLuint _ssbo;
		mutable uint32_t _binding{ 0 };

	};

	RENDELL_DECLARE_SHARED_PTR_FACTORY(OpenGLShaderBuffer)
}