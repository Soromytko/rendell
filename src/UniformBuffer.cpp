#include "UniformBuffer.h"

namespace rendell
{
	UniformBuffer::UniformBuffer(const void* data, size_t size) :
		_data(data), _size(size)
	{

	}

	const void* UniformBuffer::getData() const
	{
		return _data;
	}

	size_t UniformBuffer::getSize() const
	{
		return _size;
	}

}