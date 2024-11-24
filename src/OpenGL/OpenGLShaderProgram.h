#pragma once
#include "../ShaderProgram.h"
#include <glad/glad.h>

namespace rendell
{
	class OpenGLShaderProgram final : public ShaderProgram
	{
	public:
		OpenGLShaderProgram(std::string&& vertexSrc, std::string&& fragmentSrc);
		~OpenGLShaderProgram();
		void setVertexShaderSrc(std::string&& vertexSrc) override;
		void setFragmentShaderSrc(std::string&& fragmentSrc) override;
		bool compile(std::string* vertexInfoLog = nullptr, std::string* fragmentInfoLog = nullptr) const override;
		bool link(std::string* infoLog = nullptr) const override;
		void freeSrc() override;
		void bind() const override;
		void unbind() const override;
		uint32_t getUniformIndex(const std::string& uniformName) const;
		void setUniformBindings(const std::string& uniformName, uint32_t dataBinding);
		void setUniformBindings(uint32_t uniformIndex, uint32_t dataBinding);

	private:
		GLuint _vertexShaderId{};
		GLuint _fragmentShaderId{};
		GLuint _shaderProgramId{};
	};
}
