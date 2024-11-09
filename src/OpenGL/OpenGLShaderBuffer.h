#pragma once
#include "OpenGLUtils.h"
#include "../ShaderBuffer.h"

namespace rendell
{
	class OpenGLShaderBuffer final : public ShaderBuffer
	{
	public:
		OpenGLShaderBuffer(const void* data, size_t size);
		~OpenGLShaderBuffer();

		void bind(uint32_t layoutIndex = 0) const override;
		void unbind() const override;

		void setSubData(const void* data, size_t offset, size_t size) override;

	private:
		GLuint _ssbo;

	};
}