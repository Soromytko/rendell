#pragma once
#include "../Specification.h"

namespace rendell
{
	class OpenGLSpecification : public Specification
	{
		IndexBufferSharedPtr createIndexBuffer(std::vector<uint32_t>&& indices) const override;
		VertexBufferSharedPtr createVertexBuffer(std::vector<float>&& data) const override;
		VertexArraySharedPtr createVertexArray() const override;
		VertexArraySharedPtr createVertexArray(IndexBufferSharedPtr indexBuffer, std::initializer_list<VertexBufferSharedPtr> buffers) const override;
		ShaderProgramSharedPtr createshaderProgram(std::string&& vertexSrc, std::string&& fragmentSrc) const override;
		Texture2DSharedPtr createTexture2D(uint32_t width, uint32_t height, TextureFormat format, const uint8_t* pixels) const override;
		Texture2DArraySharedPtr createTexture2DArray(uint32_t width, uint32_t height, uint32_t count, TextureFormat format) const override;
		ShaderBufferSharedPtr createShaderBuffer(const void* data, size_t size) const override;
		UniformBufferSharedPtr createUniformBuffer(const void* data, size_t size) const override;

		void setViewport(int x, int y, int width, int height, int windowWidth, int windowHeight) override;
		void setClearBits(uint32_t clearBits) override;
		void clear() override;
		void clearColor(float r, float g, float b, float a) const override;

		void setPixelUnpackAlignment(int param) const override;

		void drawLineArrays(uint32_t firstIndex, uint32_t length) const override;
		void drawLineArraysInstanced(uint32_t firstIndex, uint32_t length, uint32_t instanceCount) const override;
		void drawLineElements(uint32_t primitiveCount) const override;
		void drawLineElementsInstanced(uint32_t primitiveCount, uint32_t instanceCount) const override;

		void drawTriangleArrays(uint32_t firstIndex, uint32_t length) const override;
		void drawTriangleArraysInstanced(uint32_t firstIndex, uint32_t length, uint32_t instanceCount) const override;
		void drawTriangleElements(uint32_t primitiveCount) const override;
		void drawTriangleElementsInstanced(uint32_t primitiveCount, uint32_t instanceCount) const override;

		void drawTriangleStripArrays(uint32_t firstIndex, uint32_t length) const override;
		void drawTriangleStripArraysInstanced(uint32_t firstIndex, uint32_t length, uint32_t instanceCount) const override;
		void drawTriangleStripElements(uint32_t primitiveCount) const override;
		void drawTriangleStripElementsInstanced(uint32_t primitiveCount, uint32_t instanceCount) const override;

	};
}