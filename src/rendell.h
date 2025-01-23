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
#include "rendell_api.h"

namespace rendell
{
	RENDELL_API bool init(const Initer& initer);
	RENDELL_API void release();

	RENDELL_API IndexBufferSharedPtr createIndexBuffer(const std::vector<uint32_t>& indices);
	RENDELL_API IndexBufferSharedPtr createIndexBuffer(std::vector<uint32_t>&& indices);

	RENDELL_API VertexBufferSharedPtr createVertexBuffer(const std::vector<float>& data);
	RENDELL_API VertexBufferSharedPtr createVertexBuffer(std::vector<float>&& data);
	RENDELL_API VertexBufferSharedPtr createVertexBuffer(const float* data, size_t size);

	RENDELL_API VertexArraySharedPtr createVertexArray();
	RENDELL_API VertexArraySharedPtr createVertexArray(IndexBufferSharedPtr indexBuffer, std::initializer_list<VertexBufferSharedPtr> buffers);

	RENDELL_API UniformBufferSharedPtr createUniformBuffer(const void* data, size_t size);

	RENDELL_API ShaderBufferSharedPtr createShaderBuffer(const void* data, size_t size);

	RENDELL_API ShaderProgramSharedPtr createShaderProgram(const std::string& vertexSrc, const std::string& fragmentSrc);
	RENDELL_API ShaderProgramSharedPtr createShaderProgram(std::string&& vertexSrc, std::string&& fragmentSrc);

	RENDELL_API Texture2DSharedPtr createTexture2D(uint32_t width, uint32_t height, TextureFormat format, const uint8_t* pixels);
	RENDELL_API Texture2DArraySharedPtr createTexture2DArray(uint32_t width, uint32_t height, uint32_t count, TextureFormat format);

	RENDELL_API void setClearBits(uint32_t clearBits);
	RENDELL_API void clear();
	RENDELL_API void clearColor(float r, float g, float b, float a);

	RENDELL_API void setViewport(int x, int y, int width, int height);
	RENDELL_API void setPixelUnpackAlignment(int param);
	
	RENDELL_API void finish();

	RENDELL_API void drawLineArrays(uint32_t firstIndex, uint32_t length);
	RENDELL_API void drawLineArraysInstanced(uint32_t firstIndex, uint32_t length, uint32_t instanceCount);
	RENDELL_API void drawLineElements(uint32_t count);
	RENDELL_API void drawLineElementsInstanced(uint32_t primitiveCount, uint32_t instanceCount);

	RENDELL_API void drawTriangleArrays(uint32_t firstIndex, uint32_t length);
	RENDELL_API void drawTriangleArraysInstanced(uint32_t firstIndex, uint32_t length, uint32_t instanceCount);
	RENDELL_API void drawTriangleElements(uint32_t count);
	RENDELL_API void drawTriangleElementsInstanced(uint32_t primitiveCount, uint32_t instanceCount);

	RENDELL_API void drawTriangleStripArrays(uint32_t firstIndex, uint32_t length);
	RENDELL_API void drawTriangleStripArraysInstanced(uint32_t firstIndex, uint32_t length, uint32_t instanceCount);
	RENDELL_API void drawTriangleStripElements(uint32_t count);
	RENDELL_API void drawTriangleStripElementsInstanced(uint32_t primitiveCount, uint32_t instanceCount);

}