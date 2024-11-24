#include "ShaderProgram.h"
#include "OpenGL/OpenGLShaderProgram.h"

namespace rendell
{
	ShaderProgram::ShaderProgram(std::string&& vertexSrc, std::string&& fragmentSrc) :
		_vertexSrc(std::move(vertexSrc)), _fragmentSrc(std::move(fragmentSrc))
	{

	}

	void ShaderProgram::setVertexShaderSrc(const std::string& vertexSrc)
	{
		std::string vertex = vertexSrc;
		setVertexShaderSrc(std::move(vertex));
	}

	void ShaderProgram::setFragmentShaderSrc(const std::string& fragmentSrc)
	{
		std::string fragment = fragmentSrc;
		setFragmentShaderSrc(std::move(fragment));
	}

	const std::string& rendell::ShaderProgram::getVertexShaderSrc() const
	{
		return _vertexSrc;
	}

	const std::string& rendell::ShaderProgram::getFragmentShaderSrc() const
	{
		return _fragmentSrc;
	}

	void ShaderProgram::setVertexShaderSrc(std::string&& vertexSrc)
	{
		_vertexSrc = std::move(vertexSrc);
	}

	void ShaderProgram::setFragmentShaderSrc(std::string&& fragmentSrc)
	{
		_fragmentSrc = std::move(fragmentSrc);
	}
}
