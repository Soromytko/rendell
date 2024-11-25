#pragma once
#include <string>

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
		virtual void setUniformBindings(const std::string& uniformName, uint32_t dataBinding) = 0;
		virtual void setUniformBindings(uint32_t uniformIndex, uint32_t dataBinding) = 0;
		virtual uint32_t getShaderBufferIndex(const std::string& bufferName) const = 0;
		virtual void setShaderBufferBinding(const std::string& bufferName, uint32_t binding) const = 0;
		virtual void setShaderBufferBinding(uint32_t bufferIndex, uint32_t binding) const = 0;

	protected:
		std::string _vertexSrc;
		std::string _fragmentSrc;

	};
}
