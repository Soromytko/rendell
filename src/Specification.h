#pragma once
#include <vector>
#include "IndexBuffer.h"
#include "VertexBuffer.h"
#include "VertexArray.h"
#include "ShaderProgram.h"
#include "TextureFormat.h"
#include "Texture2D.h"
#include "Texture2DArray.h"
#include "ShaderBuffer.h"
#include "UniformBuffer.h"
#include "defines.h"

namespace rendell
{
	class Specification
	{
	public:
		virtual IndexBuffer* createIndexBuffer(std::vector<uint32_t>&& indices) const = 0;
		virtual VertexBuffer* createVertexBuffer(std::vector<float>&& data) const = 0;
		virtual VertexArray* createVertexArray() const = 0;
		virtual VertexArray* createVertexArray(std::initializer_list<VertexBuffer*> buffers) const = 0;
		virtual ShaderProgram* createshaderProgram(std::string&& vertexSrc, std::string&& fragmentSrc) const = 0;
		virtual Texture2D* createTexture2D(uint32_t width, uint32_t height, TextureFormat format, const uint8_t* pixels) const = 0;
		virtual Texture2DArray* createTexture2DArray(uint32_t width, uint32_t height, uint32_t count, TextureFormat format) const = 0;
		virtual ShaderBuffer* createShaderBuffer(const void* data, size_t size) const = 0;
		virtual UniformBuffer* createUniformBuffer(const void* data, size_t size) const = 0;

		virtual void setClearBits(uint32_t clearBits) = 0;
		virtual void clear() = 0;
		virtual void clearColor(float r, float g, float b, float a) const = 0;

		virtual void setPixelUnpackAlignment(int param) const = 0;

		virtual void drawLineArrays(uint32_t firstIndex, uint32_t count) const = 0;
		virtual void drawLineArraysInstanced(uint32_t firstIndex, uint32_t length, uint32_t instanceCount) const = 0;
		virtual void drawLineElements(uint32_t primitiveCount) const = 0;
		virtual void drawLineElementsInstanced(uint32_t primitiveCount, uint32_t instanceCount) const = 0;

		virtual void drawTriangleArrays(uint32_t firstIndex, uint32_t count) const = 0;
		virtual void drawTriangleArraysInstanced(uint32_t firstIndex, uint32_t length, uint32_t instanceCount) const = 0;
		virtual void drawTriangleElements(uint32_t primitiveCount) const = 0;
		virtual void drawTriangleElementsInstanced(uint32_t primitiveCount, uint32_t instanceCount) const = 0;

		virtual void drawTriangleStripArrays(uint32_t firstIndex, uint32_t length) const = 0;
		virtual void drawTriangleStripArraysInstanced(uint32_t firstIndex, uint32_t length, uint32_t instanceCount) const = 0;
		virtual void drawTriangleStripElements(uint32_t primitiveCount) const = 0;
		virtual void drawTriangleStripElementsInstanced(uint32_t primitiveCount, uint32_t instanceCount) const = 0;

	protected:
		uint32_t _clearBits;
	};
}