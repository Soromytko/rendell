#pragma once
#include <string>
#include <memory>
#include "defines.h"

namespace rendell
{
	class ShaderProgram
	{
	protected:
		ShaderProgram(std::string&& vertexSrc, std::string&& fragmentSrc);

	public:
		void setVertexShaderSrc(const std::string& vertexSrc);
		void setFragmentShaderSrc(const std::string& fragmentSrc);
		const std::string& getVertexShaderSrc() const;
		const std::string& getFragmentShaderSrc() const;
		virtual void setVertexShaderSrc(std::string&& vertexSrc);
		virtual void setFragmentShaderSrc(std::string&& fragmentSrc);
		virtual bool compile(std::string* vertexInfoLog = nullptr, std::string* fragmentInfoLog = nullptr) const = 0;
		virtual bool link(std::string* infoLog = nullptr) const = 0;
		virtual void freeSrc() = 0;
		virtual void bind() const = 0;
		virtual void unbind() const = 0;

		virtual uint32_t getUniformIndex(const std::string& uniformName) const = 0;
		virtual void setUniformInt1(uint32_t uniformIndex, int value) const = 0;
		virtual void setUniformInt2(uint32_t uniformIndex, int v0, int v1) const = 0;
		virtual void setUniformInt3(uint32_t uniformIndex, int v0, int v1, int v2) const = 0;
		virtual void setUniformInt4(uint32_t uniformIndex, int v0, int v1, int v2, int v3) const = 0;
		virtual void setUniformUint1(uint32_t uniformIndex, uint32_t value) const = 0;
		virtual void setUniformFloat1(uint32_t uniformIndex, float value) const = 0;
		virtual void setUniformFloat2(uint32_t uniformIndex, float v0, float v1) const = 0;
		virtual void setUniformFloat3(uint32_t uniformIndex, float v0, float v1, float v2) const = 0;
		virtual void setUniformFloat4(uint32_t uniformIndex, float v0, float v1, float v2, float v3) const = 0;
		virtual void setUniformVec2(uint32_t uniformIndex, const float* data) const = 0;
		virtual void setUniformVec3(uint32_t uniformIndex, const float* data) const = 0;
		virtual void setUniformVec4(uint32_t uniformIndex, const float* data) const = 0;
		virtual void setUniformMat4(uint32_t uniformIndex, const float* data) const = 0;

		virtual uint32_t getUniformBufferIndex(const std::string& uniformName) const = 0;
		virtual void setUniformBufferBinding(const std::string& uniformName, uint32_t dataBinding) = 0;
		virtual void setUniformBufferBinding(uint32_t uniformIndex, uint32_t dataBinding) = 0;

		virtual uint32_t getShaderBufferIndex(const std::string& bufferName) const = 0;
		virtual void setShaderBufferBinding(const std::string& bufferName, uint32_t binding) const = 0;
		virtual void setShaderBufferBinding(uint32_t bufferIndex, uint32_t binding) const = 0;

	protected:
		std::string _vertexSrc;
		std::string _fragmentSrc;

	};

	DECLARE_SHARED_PTR_FACTORY(ShaderProgram)
}
