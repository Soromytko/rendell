#pragma once
#include <vector>
#include "IndexBuffer.h"
#include "VertexBuffer.h"
#include "VertexArray.h"
#include "ShaderProgram.h"
#include "Texture2D.h"

namespace rendell
{
	enum class SpecificationAPI
	{
		OpenGL,

	};

	struct Initer
	{
		SpecificationAPI api = SpecificationAPI::OpenGL;
		void* context = nullptr;
	};

	bool init(const Initer &initer);
	void release();

	IndexBuffer* createIndexBuffer(const std::vector<uint32_t>& indices);
	IndexBuffer* createIndexBuffer(std::vector<uint32_t>&& indices);

	VertexBuffer* createVertexBuffer(const std::vector<float>& data);
	VertexBuffer* createVertexBuffer(std::vector<float>&& data);
	VertexBuffer* createVertexBuffer(const float* data, size_t size);

	VertexArray* createVertexArray();

	ShaderProgram* createShaderProgram(const std::string& vertexSrc, const std::string& fragmentSrc);
	ShaderProgram* createShaderProgram(std::string&& vertexSrc, std::string&& fragmentSrc);

	Texture2D* createTexture2D(uint32_t width, uint32_t height, TextureFormat format, const uint8_t* pixels);

	void clearColor(float r, float g, float b, float a);
	void drawTriangles(size_t count);
}