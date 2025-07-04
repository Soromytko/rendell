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

namespace rendell
{
	typedef size_t context_id;

	context_id init(const Initer& initer);
	void release();
	void releaseContext(context_id contextId);
	void makeCurrent(context_id contextId);
	bool swapBuffers();

	IndexBufferSharedPtr createIndexBuffer(std::vector<uint32_t> indices);
	IndexBufferSharedPtr createIndexBuffer(const uint32_t* data, size_t size);

	VertexBufferSharedPtr createVertexBuffer(std::vector<float> data);
	VertexBufferSharedPtr createVertexBuffer(const float* data, size_t size);

	VertexArraySharedPtr createVertexArray();
	VertexArraySharedPtr createVertexArray(IndexBufferSharedPtr indexBuffer, std::initializer_list<VertexBufferSharedPtr> buffers);

	UniformBufferSharedPtr createUniformBuffer(const void* data, size_t size);

	ShaderBufferSharedPtr createShaderBuffer(const void* data, size_t size);

	ShaderProgramSharedPtr createShaderProgram(std::string vertexSrc, std::string fragmentSrc);

	Texture2DSharedPtr createTexture2D(uint32_t width, uint32_t height, TextureFormat format, const uint8_t* pixels);
	Texture2DArraySharedPtr createTexture2DArray(uint32_t width, uint32_t height, uint32_t count, TextureFormat format);

	void setClearBits(uint32_t clearBits);
	void clear();
	void clearColor(float r, float g, float b, float a);

	void setViewport(int x, int y, int width, int height, int windowWidth, int windowHeight);
	void setPixelUnpackAlignment(int param);

	void startScissors(int x, int y, int width, int height);
	void endScissors();

	void finish();

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