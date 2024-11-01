#include "OpenGLSpecification.h"
#include "OpenGLIndexBuffer.h"
#include "OpenGLVertexBuffer.h"
#include "OpenGLVertexArray.h"
#include "OpenGLShaderProgram.h"
#include "OpenGLTexture2D.h"

namespace rendell
{
	IndexBuffer* OpenGLSpecification::createIndexBuffer(std::vector<uint32_t>&& indices) const
	{
		return new OpenGLIndexBuffer(std::move(indices));
	}

	VertexBuffer* OpenGLSpecification::createVertexBuffer(std::vector<float>&& data) const
	{
		return new OpenGLVertexBuffer(std::move(data));
	}

	VertexArray* OpenGLSpecification::createVertexArray() const
	{
		return new OpenGLVertexArray();
	}

	ShaderProgram* OpenGLSpecification::createshaderProgram(std::string&& vertexSrc, std::string&& fragmentSrc) const
	{
		return new OpenGLShaderProgram(std::move(vertexSrc), std::move(fragmentSrc));
	}

	Texture2D* OpenGLSpecification::createTexture2D(uint32_t width, uint32_t height, TextureFormat format, const uint8_t* pixels) const
	{
		return new OpenGLTexture2D(width, height, format, pixels);
	}

	void OpenGLSpecification::clearColor(float r, float g, float b, float a) const
	{
		glClearColor(r, g, b, a);
	}

	void OpenGLSpecification::drawTriangles(size_t count) const
	{
		glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, 0);
	}

}


