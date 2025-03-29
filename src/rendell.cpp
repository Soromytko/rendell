#include <rendell/rendell_static.h>
#include <glad/glad.h>
#include <memory>
#include <unordered_map>
#include "Specification.h"
#include "IContext.h"
#include "context_creation.h"
#include "OpenGL/OpenGLSpecification.h"

namespace rendell
{
	static Specification* s_specification = nullptr;
	static std::unordered_map<context_id, IContextSharedPtr> s_contexts;
	static IContextSharedPtr s_currentContext = nullptr;

	static context_id generate_context_id()
	{
		static size_t counter;
		return ++counter;
	}

	context_id init(const Initer& initer)
	{
		const IContextSharedPtr context = createContext(initer);
		if (!context->isInitialized())
		{
			std::cerr << "ERROR: Failed to initialize OpenGL context" << std::endl;
			return 0;
		}

		std::cout << context->getName() << std::endl;

		s_currentContext = context;
		context->makeCurrent();
		s_specification = context->getSpecification();

		const context_id contextId = generate_context_id();
		s_contexts[contextId] = context;
		return contextId;
	}

	void release()
	{
		s_contexts.clear();
	}

	void releaseContext(context_id contextId)
	{
		auto it = s_contexts.find(contextId);
		if (it == s_contexts.end())
		{
			std::cerr << "ERROR: Invalid context ID " << contextId << std::endl;
		}

		s_contexts.erase(it);
	}

	void makeCurrent(context_id contextId)
	{
		auto it = s_contexts.find(contextId);
		if (it == s_contexts.end())
		{
			std::cerr << "ERROR: Invalid context ID " << contextId << std::endl;
		}

		s_currentContext = it->second;
		s_currentContext->makeCurrent();
		s_specification = s_currentContext->getSpecification();
	}

	bool swapBuffers()
	{
		return s_currentContext->swapBuffers();
	}

	IndexBufferSharedPtr createIndexBuffer(const std::vector<uint32_t>& indices)
	{
		std::vector<uint32_t> value = indices;
		return createIndexBuffer(std::move(value));
	}

	IndexBufferSharedPtr createIndexBuffer(std::vector<uint32_t>&& indices)
	{
		return s_specification->createIndexBuffer(std::move(indices));
	}

	VertexBufferSharedPtr createVertexBuffer(const std::vector<float>& data)
	{
		std::vector<float> value = data;
		return createVertexBuffer(std::move(value));
	}

	VertexBufferSharedPtr createVertexBuffer(std::vector<float>&& data)
	{
		return s_specification->createVertexBuffer(std::move(data));
	}

	VertexBufferSharedPtr createVertexBuffer(const float* data, size_t size)
	{
		std::vector<float> value;
		value.resize(size);
		for (size_t i = 0; i < size; i++) {
			value[i] = data[i];
		}
		return createVertexBuffer(std::move(value));
	}

	VertexArraySharedPtr createVertexArray()
	{
		return s_specification->createVertexArray();
	}

	VertexArraySharedPtr createVertexArray(IndexBufferSharedPtr indexBuffer, std::initializer_list<VertexBufferSharedPtr> buffers)
	{
		return s_specification->createVertexArray(indexBuffer, buffers);
	}

	UniformBufferSharedPtr createUniformBuffer(const void* data, size_t size)
	{
		return s_specification->createUniformBuffer(data, size);
	}

	ShaderBufferSharedPtr createShaderBuffer(const void* data, size_t size)
	{
		return s_specification->createShaderBuffer(data, size);
	}

	ShaderProgramSharedPtr createShaderProgram(const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		std::string vertex = vertexSrc;
		std::string fragment = fragmentSrc;
		return createShaderProgram(std::move(vertex), std::move(fragment));
	}

	ShaderProgramSharedPtr createShaderProgram(std::string&& vertexSrc, std::string&& fragmentSrc)
	{
		return s_specification->createshaderProgram(std::move(vertexSrc), std::move(fragmentSrc));
	}

	Texture2DSharedPtr createTexture2D(uint32_t width, uint32_t height, TextureFormat format, const uint8_t* pixels)
	{
		return s_specification->createTexture2D(width, height, format, pixels);
	}

	Texture2DArraySharedPtr createTexture2DArray(uint32_t width, uint32_t height, uint32_t count, TextureFormat format)
	{
		return s_specification->createTexture2DArray(width, height, count, format);
	}

	void setClearBits(uint32_t clearBits)
	{
		s_specification->setClearBits(clearBits);
	}

	void clear()
	{
		s_specification->clear();
	}

	void clearColor(float r, float g, float b, float a)
	{
		s_specification->clearColor(r, g, b, a);
	}

	void setViewport(int x, int y, int width, int height)
	{
		glViewport(x, y, width, height);
	}

	void setPixelUnpackAlignment(int param)
	{
		s_specification->setPixelUnpackAlignment(param);
	}

	void finish()
	{
		glFinish();
	}

	void drawLineArrays(uint32_t firstIndex, uint32_t length)
	{
		s_specification->drawLineArrays(firstIndex, length);
	}

	void drawLineArraysInstanced(uint32_t firstIndex, uint32_t length, uint32_t instanceCount)
	{
		s_specification->drawLineArraysInstanced(firstIndex, length, instanceCount);
	}

	void drawLineElements(uint32_t primitiveCount)
	{
		s_specification->drawLineElements(primitiveCount);
	}

	void drawLineElementsInstanced(uint32_t primitiveCount, uint32_t instanceCount)
	{
		s_specification->drawLineElementsInstanced(primitiveCount, instanceCount);
	}

	void drawTriangleArrays(uint32_t firstIndex, uint32_t length)
	{
		s_specification->drawTriangleArrays(firstIndex, length);
	}

	void drawTriangleArraysInstanced(uint32_t firstIndex, uint32_t length, uint32_t instanceCount)
	{
		s_specification->drawTriangleArraysInstanced(firstIndex, length, instanceCount);
	}

	void drawTriangleElements(uint32_t primitiveCount)
	{
		s_specification->drawTriangleElements(primitiveCount);
	}

	void drawTriangleElementsInstanced(uint32_t primitiveCount, uint32_t instanceCount)
	{
		s_specification->drawTriangleElementsInstanced(primitiveCount, instanceCount);
	}

	void drawTriangleStripArrays(uint32_t firstIndex, uint32_t length)
	{
		s_specification->drawTriangleStripArrays(firstIndex, length);
	}

	void drawTriangleStripArraysInstanced(uint32_t firstIndex, uint32_t length, uint32_t instanceCount)
	{
		s_specification->drawTriangleStripArraysInstanced(firstIndex, length, instanceCount);
	}

	void drawTriangleStripElements(uint32_t primitiveCount)
	{
		s_specification->drawTriangleStripElements(primitiveCount);
	}

	void drawTriangleStripElementsInstanced(uint32_t primitiveCount, uint32_t instanceCount)
	{
		s_specification->drawTriangleStripElementsInstanced(primitiveCount, instanceCount);
	}

}
