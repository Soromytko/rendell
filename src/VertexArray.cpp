#include "VertexArray.h"
#include "OpenGL/OpenGLVertexArray.h"

namespace rendell
{
	VertexArray::VertexArray(std::initializer_list<VertexBufferSharedPtr> buffers)
	{
		for (auto it = buffers.begin(); it != buffers.end(); it++)
		{
			_vertexBuffers.push_back(*it);
		}
	}

	void VertexArray::setIndexBuffer(IndexBufferSharedPtr indexBuffer)
	{
		_indexBuffer = indexBuffer;
	}

	void VertexArray::addVertexBuffer(VertexBufferSharedPtr vertexBuffer)
	{
		_vertexBuffers.push_back(vertexBuffer);
	}

	const std::vector<VertexBufferSharedPtr>& VertexArray::getVertexBuffers() const
	{
		return _vertexBuffers;
	}

	const IndexBufferSharedPtr& VertexArray::getIndexBuffer() const
	{
		return _indexBuffer;
	}
}
