#include "OpenGLVertexArray.h"

using namespace rendell;

OpenGLVertexArray::OpenGLVertexArray()
{
	glCreateVertexArrays(1, &_vertexArrayId);
}

rendell::OpenGLVertexArray::OpenGLVertexArray(std::initializer_list<VertexBuffer*> buffers) :
	VertexArray(std::move(buffers))
{
	glCreateVertexArrays(1, &_vertexArrayId);
}

OpenGLVertexArray::~OpenGLVertexArray()
{
	glCreateVertexArrays(1, &_vertexArrayId);
}

void OpenGLVertexArray::bind() const
{
	glBindVertexArray(_vertexArrayId);
}

void OpenGLVertexArray::unbind() const
{
	glBindVertexArray(0);
}

void OpenGLVertexArray::setIndexBuffer(IndexBuffer* indexBuffer)
{
	VertexArray::setIndexBuffer(indexBuffer);
	bind();
	indexBuffer->bind();
}

static GLenum convertShaderTypeToOpenGLType(DataType type)
{
	switch (type)
	{
	case DataType::int1: case DataType::int2: case DataType::int3: return GL_INT;
	case DataType::float1: case DataType::float2: case DataType::float3: return GL_FLOAT;
	}
	return 0;
}

void OpenGLVertexArray::addVertexBuffer(VertexBuffer* vertexBuffer)
{
	VertexArray::addVertexBuffer(vertexBuffer);

	bind();
	vertexBuffer->bind();

	int index = 0;
	for (const VertexBufferLayout& layout : vertexBuffer->getLayouts())
	{
		const GLint size = layout.getComponentCountByShaderType();
		const GLenum type = convertShaderTypeToOpenGLType(layout.getType());
		const GLboolean normalized = layout.getNormalized() ? GL_TRUE : GL_FALSE;
		const GLsizei stride = vertexBuffer->getStride();
		const void* offset = reinterpret_cast<const void*>(layout.getOffset());

		glEnableVertexAttribArray(index);

		switch (layout.getType())
		{
		case DataType::int1: case DataType::int2: case DataType::int3: case DataType::int4:
		{
			glVertexAttribIPointer(index, size, type, stride, offset);
			break;
		}
		case DataType::float1: case DataType::float2: case DataType::float3: case DataType::float4:
			glVertexAttribPointer(index, size, type, normalized, stride, offset);
			break;
		}

		index++;
	}

}
