#pragma once
#include <vector>
#include "IndexBuffer.h"
#include "VertexBuffer.h"
#include "VertexArray.h"
#include "ShaderProgram.h"
#include "Texture2D.h"

namespace rendell
{
	class Specification
	{
	public:
		virtual IndexBuffer* createIndexBuffer(std::vector<uint32_t>&& indices) const = 0;
		virtual VertexBuffer* createVertexBuffer(std::vector<float>&& data) const = 0;
		virtual VertexArray* createVertexArray() const = 0;
		virtual ShaderProgram* createshaderProgram(std::string&& vertexSrc, std::string&& fragmentSrc) const = 0;
		virtual Texture2D* createTexture2D(uint32_t width, uint32_t height, TextureFormat format, const uint8_t* pixels) const = 0;

		virtual void clearColor(float r, float g, float b, float a) const = 0;
		virtual void drawTriangles(size_t count) const = 0;
	};
}