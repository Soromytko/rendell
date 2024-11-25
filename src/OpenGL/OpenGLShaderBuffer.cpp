#include "OpenGLShaderBuffer.h"

namespace rendell
{
	OpenGLShaderBuffer::OpenGLShaderBuffer(const void* data, size_t size) :
		ShaderBuffer(data, size)
	{
		glGenBuffers(1, &_ssbo);
		glBindBuffer(GL_SHADER_STORAGE_BUFFER, _ssbo);
		glBufferData(GL_SHADER_STORAGE_BUFFER, _size, _data, GL_DYNAMIC_DRAW);
		glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
	}

	OpenGLShaderBuffer::~OpenGLShaderBuffer()
	{
		glDeleteBuffers(1, &_ssbo);
	}

	void OpenGLShaderBuffer::bind(uint32_t binding) const
	{
		_binding = binding;
		glBindBufferBase(GL_SHADER_STORAGE_BUFFER, _binding, _ssbo);
	}

	void OpenGLShaderBuffer::unbind() const
	{
		glBindBufferBase(GL_SHADER_STORAGE_BUFFER, _binding, 0);
	}

	void OpenGLShaderBuffer::setSubData(const void* data, size_t size, size_t offset)
	{
		glBindBuffer(GL_SHADER_STORAGE_BUFFER, _ssbo);
		glBufferSubData(GL_SHADER_STORAGE_BUFFER, offset, size, data);
		glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
	}
}