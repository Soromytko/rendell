#include "VertexArray.h"
#include "OpenGL/OpenGLVertexArray.h"

using namespace rendell;

VertexArray::VertexArray(std::initializer_list<VertexBuffer*> buffers)
{
	for (auto it = buffers.begin(); it != buffers.end(); it++)
	{
		_vertexBuffers.push_back(std::shared_ptr<VertexBuffer>(*it));
	}
}

void VertexArray::setIndexBuffer(IndexBuffer* indexBuffer)
{
	_indexBuffer.reset(indexBuffer);
}

void VertexArray::addVertexBuffer(VertexBuffer* vertexBuffer)
{
	std::shared_ptr<VertexBuffer> p;
	p.reset(vertexBuffer);
	_vertexBuffers.push_back(std::move(p));
}

const std::vector<std::shared_ptr<VertexBuffer>>& VertexArray::getVertexBuffers() const
{
	return _vertexBuffers;
}

const std::shared_ptr<IndexBuffer>& VertexArray::getIndexBuffer() const
{
	return _indexBuffer;
}
