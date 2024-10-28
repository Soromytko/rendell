#pragma once
#include "../Specification.h"

namespace rendell
{
	class OpenGLSpecification : public Specification
	{
		IndexBuffer* createIndexBuffer(std::vector<uint32_t>&& indices) const override;
		VertexBuffer* createVertexBuffer(std::vector<float>&& data) const override;
		VertexArray* createVertexArray() const override;
		ShaderProgram* createshaderProgram(std::string&& vertexSrc, std::string&& fragmentSrc) const override;
		void clearColor(float r, float g, float b, float a) const override;
		void drawTriangles(size_t count) const override;

	};
}