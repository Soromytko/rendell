#include <rendell/IndexBuffer.h>
#include <memory>
#include "OpenGL/OpenGLIndexBuffer.h"

namespace rendell
{
	IndexBuffer::IndexBuffer(std::vector<uint32_t>&& indices)
	{
		_indices = std::move(indices);
	}

	const std::vector<uint32_t>& IndexBuffer::getIndices() const
	{
		return _indices;
	}
}
