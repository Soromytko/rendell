#include "OpenGLUniformBuffer.h"

namespace rendell
{
	OpenGLUniformBuffer::OpenGLUniformBuffer(const void* data, size_t size) :
		UniformBuffer(data, size)
	{
		glCreateBuffers(1, &_id);
		glNamedBufferData(_id, _size, _data, GL_DYNAMIC_DRAW);
	}

	void OpenGLUniformBuffer::bind(uint32_t binding) const
	{
		_binding = binding;
		glBindBufferBase(GL_UNIFORM_BUFFER, _binding, _id);
	}

	void OpenGLUniformBuffer::unbind() const
	{
		glBindBufferBase(GL_UNIFORM_BUFFER, _binding, 0);
	}

	void OpenGLUniformBuffer::setSubData(const void* data, size_t size, size_t offset) const
	{
		glBindBuffer(GL_SHADER_STORAGE_BUFFER, _id);
		glBufferSubData(GL_UNIFORM_BUFFER, offset, size, data);
		glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
	}
}