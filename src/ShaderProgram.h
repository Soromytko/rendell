#pragma once
#include <string>
#include "DataType.h"

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
		virtual uint32_t getUniformBlockIndex(const std::string& uniformName) const = 0;

		virtual void setUniformValue(const std::string& uniformName, DataType type, const char* data) = 0;
		virtual void setUniformValue(uint32_t uniformIndex, DataType type, const char* data) = 0;
		virtual void setIntUniform(uint32_t uniformIndex, int value) = 0;
		virtual void setFloatUniform(uint32_t uniformIndex, float value) = 0;

		virtual void setUniformBlockBindings(const std::string& uniformName, uint32_t dataBinding) = 0;
		virtual void setUniformBlockBindings(uint32_t uniformIndex, uint32_t dataBinding) = 0;

	protected:
		std::string _vertexSrc;
		std::string _fragmentSrc;

	};
}
