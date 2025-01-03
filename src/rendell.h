#pragma once
#include <vector>
#include "IndexBuffer.h"
#include "VertexBuffer.h"
#include "VertexArray.h"
#include "ShaderProgram.h"
#include "Texture2D.h"
#include "Texture2DArray.h"
#include "ShaderBuffer.h"
#include "UniformBuffer.h"
#include "defines.h"

namespace rendell
{
	bool init(const Initer& initer);
	void release();

	IndexBuffer* createIndexBuffer(const std::vector<uint32_t>& indices);
	IndexBuffer* createIndexBuffer(std::vector<uint32_t>&& indices);

	VertexBuffer* createVertexBuffer(const std::vector<float>& data);
	VertexBuffer* createVertexBuffer(std::vector<float>&& data);
	VertexBuffer* createVertexBuffer(const float* data, size_t size);

	VertexArray* createVertexArray();
	VertexArray* createVertexArray(std::initializer_list<VertexBuffer*> buffers);

	UniformBuffer* createUniformBuffer(const void* data, size_t size);

	ShaderBuffer* createShaderBuffer(const void* data, size_t size);

	ShaderProgram* createShaderProgram(const std::string& vertexSrc, const std::string& fragmentSrc);
	ShaderProgram* createShaderProgram(std::string&& vertexSrc, std::string&& fragmentSrc);

	Texture2D* createTexture2D(uint32_t width, uint32_t height, TextureFormat format, const uint8_t* pixels);
	Texture2DArray* createTexture2DArray(uint32_t width, uint32_t height, uint32_t count, TextureFormat format);

	void setClearBits(uint32_t clearBits);
	void clear();
	void clearColor(float r, float g, float b, float a);

	void setPixelUnpackAlignment(int param);

	void drawLineArrays(uint32_t firstIndex, uint32_t length);
	void drawLineArraysInstanced(uint32_t firstIndex, uint32_t length, uint32_t instanceCount);
	void drawLineElements(uint32_t count);
	void drawLineElementsInstanced(uint32_t primitiveCount, uint32_t instanceCount);

	void drawTriangleArrays(uint32_t firstIndex, uint32_t length);
	void drawTriangleArraysInstanced(uint32_t firstIndex, uint32_t length, uint32_t instanceCount);
	void drawTriangleElements(uint32_t count);
	void drawTriangleElementsInstanced(uint32_t primitiveCount, uint32_t instanceCount);

	void drawTriangleStripArrays(uint32_t firstIndex, uint32_t length);
	void drawTriangleStripArraysInstanced(uint32_t firstIndex, uint32_t length, uint32_t instanceCount);
	void drawTriangleStripElements(uint32_t count);
	void drawTriangleStripElementsInstanced(uint32_t primitiveCount, uint32_t instanceCount);

}