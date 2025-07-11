#pragma once
#include <vector>
#include <rendell/IndexBuffer.h>
#include <rendell/VertexBuffer.h>
#include <rendell/VertexArray.h>
#include <rendell/ShaderProgram.h>
#include <rendell/TextureFormat.h>
#include <rendell/Texture2D.h>
#include <rendell/Texture2DArray.h>
#include <rendell/ShaderBuffer.h>
#include <rendell/UniformBuffer.h>

namespace rendell
{
	class Specification
	{
	public:
		virtual IndexBufferSharedPtr createIndexBuffer(std::vector<uint32_t>&& indices) const = 0;
		virtual VertexBufferSharedPtr createVertexBuffer(std::vector<float>&& data) const = 0;
		virtual VertexArraySharedPtr createVertexArray() const = 0;
		virtual VertexArraySharedPtr createVertexArray(IndexBufferSharedPtr indexBuffer, std::initializer_list<VertexBufferSharedPtr> buffers) const = 0;
		virtual ShaderProgramSharedPtr createshaderProgram(std::string&& vertexSrc, std::string&& fragmentSrc) const = 0;
		virtual Texture2DSharedPtr createTexture2D(uint32_t width, uint32_t height, TextureFormat format, const uint8_t* pixels) const = 0;
		virtual Texture2DArraySharedPtr createTexture2DArray(uint32_t width, uint32_t height, uint32_t count, TextureFormat format) const = 0;
		virtual ShaderBufferSharedPtr createShaderBuffer(const void* data, size_t size) const = 0;
		virtual UniformBufferSharedPtr createUniformBuffer(const void* data, size_t size) const = 0;

		virtual void setViewport(int x, int y, int width, int height, int windowWidth, int windowHeight) = 0;
		virtual void setClearBits(uint32_t clearBits) = 0;
		virtual void clear() = 0;
		virtual void clearColor(float r, float g, float b, float a) const = 0;

		virtual void setPixelUnpackAlignment(int param) const = 0;

		virtual void startScissors(int x, int y, int width, int height) const = 0;
		virtual void endScissors() const = 0;

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