#include "VertexBuffer.h"
#include "OpenGL/OpenGLVertexBuffer.h"

namespace rendell
{
	VertexBuffer::VertexBuffer(std::vector<float>&& data)
	{
		_data = std::move(data);
	}

	const std::vector<float>& VertexBuffer::getData() const
	{
		return _data;
	}

	int VertexBuffer::getStride() const
	{
		return _stride;
	}

	const std::vector<VertexBufferLayout>& VertexBuffer::getLayouts() const
	{
		return _layouts;
	}

	void VertexBuffer::setLayouts(const std::vector<VertexBufferLayout>& layouts)
	{
		_layouts = layouts;
		calculateOffsetsAndStride();
	}

	void VertexBuffer::calculateOffsetsAndStride()
	{
		size_t offset = 0;
		_stride = 0;
		for (VertexBufferLayout& layout : _layouts)
		{
			layout.setOffset(offset);
			offset += layout.getSize();
			_stride += static_cast<int>(layout.getSize());
		}
	}
}
