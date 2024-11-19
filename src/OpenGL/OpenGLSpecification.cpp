#include "OpenGLSpecification.h"
#include "OpenGLIndexBuffer.h"
#include "OpenGLVertexBuffer.h"
#include "OpenGLVertexArray.h"
#include "OpenGLShaderProgram.h"
#include "OpenGLTexture2D.h"
#include "OpenGLTexture2DArray.h"
#include "OpenGLShaderBuffer.h"

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

	VertexArray* OpenGLSpecification::createVertexArray(std::initializer_list<VertexBuffer*> buffers) const
	{
		return new OpenGLVertexArray(std::move(buffers));
	}

	ShaderProgram* OpenGLSpecification::createshaderProgram(std::string&& vertexSrc, std::string&& fragmentSrc) const
	{
		return new OpenGLShaderProgram(std::move(vertexSrc), std::move(fragmentSrc));
	}

	Texture2D* OpenGLSpecification::createTexture2D(uint32_t width, uint32_t height, TextureFormat format, const uint8_t* pixels) const
	{
		return new OpenGLTexture2D(width, height, format, pixels);
	}

	Texture2DArray* OpenGLSpecification::createTexture2DArray(uint32_t width, uint32_t height, uint32_t count, TextureFormat format) const
	{
		return new OpenGLTexture2DArray(width, height, count, format);
	}

	ShaderBuffer* OpenGLSpecification::createShaderBuffer(const void* data, size_t size) const
	{
		return new OpenGLShaderBuffer(data, size);
	}

	void OpenGLSpecification::clearColor(float r, float g, float b, float a) const
	{
		glClearColor(r, g, b, a);
	}

	void OpenGLSpecification::drawLineArrays(uint32_t firstIndex, uint32_t length) const
	{
		glDrawArrays(GL_LINES, firstIndex, length);
	}

	void OpenGLSpecification::drawLineArraysInstanced(uint32_t firstIndex, uint32_t length, uint32_t instanceCount) const
	{
		glDrawArraysInstanced(GL_LINES, firstIndex, length, instanceCount);
	}

	void OpenGLSpecification::drawLineElements(uint32_t primitiveCount) const
	{
		glDrawElements(GL_LINES, primitiveCount, GL_UNSIGNED_INT, 0);
	}

	void OpenGLSpecification::drawLineElementsInstanced(uint32_t primitiveCount, uint32_t instanceCount) const
	{
		glDrawElementsInstanced(GL_LINES, primitiveCount, GL_UNSIGNED_INT, 0, instanceCount);
	}

	void OpenGLSpecification::drawTriangleArrays(uint32_t firstIndex, uint32_t length) const
	{
		glDrawArrays(GL_TRIANGLES, firstIndex, length);
	}

	void OpenGLSpecification::drawTriangleArraysInstanced(uint32_t firstIndex, uint32_t length, uint32_t instanceCount) const
	{
		glDrawArraysInstanced(GL_TRIANGLES, firstIndex, length, instanceCount);
	}

	void OpenGLSpecification::drawTriangleElements(uint32_t primitiveCount) const
	{
		glDrawElements(GL_TRIANGLES, primitiveCount, GL_UNSIGNED_INT, 0);
	}

	void OpenGLSpecification::drawTriangleElementsInstanced(uint32_t primitiveCount, uint32_t instanceCount) const
	{
		glDrawElementsInstanced(GL_TRIANGLES, primitiveCount, GL_UNSIGNED_INT, 0, instanceCount);
	}

	void OpenGLSpecification::drawTriangleStripArrays(uint32_t firstIndex, uint32_t length) const
	{
		glDrawArrays(GL_TRIANGLE_STRIP, firstIndex, length);
	}

	void OpenGLSpecification::drawTriangleStripArraysInstanced(uint32_t firstIndex, uint32_t length, uint32_t instanceCount) const
	{
		glDrawArraysInstanced(GL_TRIANGLE_STRIP, firstIndex, length, instanceCount);
	}

	void OpenGLSpecification::drawTriangleStripElements(uint32_t primitiveCount) const
	{
		glDrawElements(GL_TRIANGLE_STRIP, primitiveCount, GL_UNSIGNED_INT, 0);
	}

	void OpenGLSpecification::drawTriangleStripElementsInstanced(uint32_t primitiveCount, uint32_t instanceCount) const
	{
		glDrawElementsInstanced(GL_TRIANGLE_STRIP, primitiveCount, GL_UNSIGNED_INT, 0, instanceCount);
	}

}


