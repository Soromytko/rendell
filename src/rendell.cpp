#include <glad/glad.h>
#include "rendell.h"
#include "Specification.h"
#include "OpenGL/OpenGLSpecification.h"

namespace rendell
{
	static Specification* s_specification = nullptr;

	static bool initOpenGLSpecification(const Initer& initer)
	{
		s_specification = new OpenGLSpecification();
		return gladLoadGLLoader((GLADloadproc)initer.context);
	}

	bool init(const Initer& initer)
	{
		switch (initer.api)
		{
		case SpecificationAPI::OpenGL: return initOpenGLSpecification(initer);
		default: return false;
		}

		return true;
	}

	void release()
	{
		if (s_specification)
		{
			delete s_specification;
			s_specification = nullptr;
		}
	}

	IndexBuffer* createIndexBuffer(const std::vector<uint32_t>& indices)
	{
		std::vector<uint32_t> value = indices;
		return createIndexBuffer(std::move(value));
	}

	IndexBuffer* createIndexBuffer(std::vector<uint32_t>&& indices)
	{
		return s_specification->createIndexBuffer(std::move(indices));
	}

	VertexBuffer* createVertexBuffer(const std::vector<float>& data)
	{
		std::vector<float> value = data;
		return createVertexBuffer(std::move(value));
	}

	VertexBuffer* createVertexBuffer(std::vector<float>&& data)
	{
		return s_specification->createVertexBuffer(std::move(data));
	}

	VertexBuffer* createVertexBuffer(const float* data, size_t size)
	{
		std::vector<float> value;
		value.resize(size);
		for (size_t i = 0; i < size; i++) {
			value[i] = data[i];
		}
		return createVertexBuffer(std::move(value));
	}

	VertexArray* createVertexArray()
	{
		return s_specification->createVertexArray();
	}

	ShaderProgram* createShaderProgram(const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		std::string vertex = vertexSrc;
		std::string fragment = fragmentSrc;
		return createShaderProgram(std::move(vertex), std::move(fragment));
	}

	ShaderProgram* createShaderProgram(std::string&& vertexSrc, std::string&& fragmentSrc)
	{
		return s_specification->createshaderProgram(std::move(vertexSrc), std::move(fragmentSrc));
	}

	void clearColor(float r, float g, float b, float a)
	{
		s_specification->clearColor(r, g, b, a);
	}

	void drawTriangles(size_t count)
	{
		s_specification->drawTriangles(count);
	}

}
