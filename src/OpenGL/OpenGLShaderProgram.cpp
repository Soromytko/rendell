#include "OpenGLShaderProgram.h"
#define LOG_INFO_BUFFER_SIZE 512

namespace rendell
{
	static GLuint createShader(const std::string& src, GLuint type)
	{
		GLuint result = glCreateShader(type);
		const GLchar* srcPtr = static_cast<const GLchar*>(src.c_str());
		glShaderSource(result, 1, &srcPtr, NULL);
		return result;
	}

	OpenGLShaderProgram::OpenGLShaderProgram(std::string&& vertexSrc, std::string&& fragmentSrc) :
		ShaderProgram(std::move(vertexSrc), std::move(fragmentSrc))
	{
		_vertexShaderId = createShader(_vertexSrc, GL_VERTEX_SHADER);
		_fragmentShaderId = createShader(_fragmentSrc, GL_FRAGMENT_SHADER);
		_shaderProgramId = glCreateProgram();
	}

	OpenGLShaderProgram::~OpenGLShaderProgram()
	{
		glDeleteShader(_vertexShaderId);
		glDeleteShader(_fragmentShaderId);
		glDeleteProgram(_shaderProgramId);
	}

	void OpenGLShaderProgram::setVertexShaderSrc(std::string&& vertexSrc)
	{
		ShaderProgram::setVertexShaderSrc(std::move(vertexSrc));
		glDeleteShader(_vertexShaderId);
		_vertexShaderId = createShader(_vertexSrc, GL_VERTEX_SHADER);
	}

	void OpenGLShaderProgram::setFragmentShaderSrc(std::string&& fragmentSrc)
	{
		ShaderProgram::setFragmentShaderSrc(std::move(fragmentSrc));
		glDeleteShader(_fragmentShaderId);
		_fragmentShaderId = createShader(_fragmentSrc, GL_FRAGMENT_SHADER);
	}

	static bool IsShaderCompiledSuccessfully(GLuint shaderId, std::string* infoLog)
	{
		int success;
		glCompileShader(shaderId);
		glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);
		if (!success && infoLog)
		{
			char infoLogBuffer[LOG_INFO_BUFFER_SIZE];
			glGetShaderInfoLog(shaderId, LOG_INFO_BUFFER_SIZE, NULL, infoLogBuffer);
			*infoLog = infoLogBuffer;
		}
		return success;
	}

	bool OpenGLShaderProgram::compile(std::string* vertexInfoLog, std::string* fragmentInfoLog) const
	{
		const bool vertexResult = IsShaderCompiledSuccessfully(_vertexShaderId, vertexInfoLog);
		const bool fragmentResult = IsShaderCompiledSuccessfully(_fragmentShaderId, fragmentInfoLog);
		return vertexResult && fragmentResult;
	}

	bool OpenGLShaderProgram::link(std::string* infoLog) const
	{
		glAttachShader(_shaderProgramId, _vertexShaderId);
		glAttachShader(_shaderProgramId, _fragmentShaderId);
		glLinkProgram(_shaderProgramId);

		int success;
		glGetProgramiv(_shaderProgramId, GL_LINK_STATUS, &success);
		if (!success && infoLog)
		{
			char infoLogBuffer[LOG_INFO_BUFFER_SIZE];
			glGetProgramInfoLog(_shaderProgramId, LOG_INFO_BUFFER_SIZE, NULL, infoLogBuffer);
			*infoLog = infoLogBuffer;
		}
		return success;
	}

	void OpenGLShaderProgram::freeSrc()
	{
		glDeleteShader(_vertexShaderId);
		glDeleteShader(_fragmentShaderId);
		_vertexSrc.clear();
		_fragmentSrc.clear();
	}

	void OpenGLShaderProgram::bind() const
	{
		glUseProgram(_shaderProgramId);
	}

	void OpenGLShaderProgram::unbind() const
	{
		glUseProgram(0);
	}

	uint32_t OpenGLShaderProgram::getUniformIndex(const std::string& uniformName) const
	{
		return glGetUniformLocation(_shaderProgramId, uniformName.c_str());
	}

	void OpenGLShaderProgram::setUniformInt1(uint32_t uniformIndex, int value) const
	{
		glProgramUniform1i(
			_shaderProgramId,
			static_cast<GLint>(uniformIndex),
			static_cast<GLint>(value)
		);
	}

	void OpenGLShaderProgram::setUniformInt2(uint32_t uniformIndex, int v0, int v1) const
	{
		glProgramUniform2i(
			_shaderProgramId,
			static_cast<GLint>(uniformIndex),
			v0, v1
		);
	}

	void OpenGLShaderProgram::setUniformInt3(uint32_t uniformIndex, int v0, int v1, int v2) const
	{
		glProgramUniform3i(
			_shaderProgramId,
			static_cast<GLint>(uniformIndex),
			v0, v1, v2
		);
	}

	void OpenGLShaderProgram::setUniformInt4(uint32_t uniformIndex, int v0, int v1, int v2, int v3) const
	{
		glProgramUniform4i(
			_shaderProgramId,
			static_cast<GLint>(uniformIndex),
			v0, v1, v2, v3
		);
	}

	void OpenGLShaderProgram::setUniformUint1(uint32_t uniformIndex, uint32_t value) const
	{
		glProgramUniform1ui(
			_shaderProgramId,
			static_cast<GLint>(uniformIndex),
			static_cast<GLuint>(value)
		);
	}

	void OpenGLShaderProgram::setUniformFloat1(uint32_t uniformIndex, float value) const
	{
		glProgramUniform1f(
			_shaderProgramId,
			static_cast<GLint>(uniformIndex),
			static_cast<GLfloat>(value)
		);
	}

	void OpenGLShaderProgram::setUniformFloat2(uint32_t uniformIndex, float v0, float v1) const
	{
		glProgramUniform2f(
			_shaderProgramId,
			static_cast<GLint>(uniformIndex),
			v0, v1
		);
	}

	void OpenGLShaderProgram::setUniformFloat3(uint32_t uniformIndex, float v0, float v1, float v2) const
	{
		glProgramUniform3f(
			_shaderProgramId,
			static_cast<GLint>(uniformIndex),
			v0, v1, v2
		);
	}

	void OpenGLShaderProgram::setUniformFloat4(uint32_t uniformIndex, float v0, float v1, float v2, float v3) const
	{
		glProgramUniform4f(
			_shaderProgramId,
			static_cast<GLint>(uniformIndex),
			v0, v1, v2, v3
		);
	}

	void OpenGLShaderProgram::setUniformVec2(uint32_t uniformIndex, const float* data) const
	{
		glProgramUniform2fv(
			_shaderProgramId,
			static_cast<GLint>(uniformIndex),
			0,
			static_cast<const GLfloat*>(data)
		);
	}

	void OpenGLShaderProgram::setUniformVec3(uint32_t uniformIndex, const float* data) const
	{
		glProgramUniform3fv(
			_shaderProgramId,
			static_cast<GLint>(uniformIndex),
			1,
			static_cast<const GLfloat*>(data)
		);
	}

	void OpenGLShaderProgram::setUniformVec4(uint32_t uniformIndex, const float* data) const
	{
		glProgramUniform4fv(
			_shaderProgramId,
			static_cast<GLint>(uniformIndex),
			1,
			static_cast<const GLfloat*>(data)
		);
	}

	void OpenGLShaderProgram::setUniformMat4(uint32_t uniformIndex, const float* data) const
	{
		glProgramUniformMatrix4fv(
			_shaderProgramId,
			static_cast<GLint>(uniformIndex),
			1,
			GL_FALSE,
			static_cast<const GLfloat*>(data)
		);
	}

	uint32_t OpenGLShaderProgram::getUniformBufferIndex(const std::string& uniformName) const
	{
		return glGetUniformBlockIndex(
			_shaderProgramId,
			static_cast<const GLchar*>(uniformName.c_str())
		);
	}

	void OpenGLShaderProgram::setUniformBufferBinding(const std::string& uniformName, uint32_t dataBinding)
	{
		const uint32_t index = getUniformBufferIndex(uniformName);
		setUniformBufferBinding(index, dataBinding);
	}

	void OpenGLShaderProgram::setUniformBufferBinding(uint32_t uniformIndex, uint32_t dataBinding)
	{
		glUniformBlockBinding(_shaderProgramId, uniformIndex, dataBinding);
	}

	uint32_t OpenGLShaderProgram::getShaderBufferIndex(const std::string& bufferName) const
	{
		return glGetProgramResourceIndex(_shaderProgramId, GL_SHADER_STORAGE_BLOCK, bufferName.c_str());
	}

	void OpenGLShaderProgram::setShaderBufferBinding(const std::string& bufferName, uint32_t binding) const
	{
		const uint32_t index = getShaderBufferIndex(bufferName);
		setShaderBufferBinding(index, binding);
	}

	void OpenGLShaderProgram::setShaderBufferBinding(uint32_t bufferIndex, uint32_t binding) const
	{
		glShaderStorageBlockBinding(_shaderProgramId, bufferIndex, binding);
	}

}
