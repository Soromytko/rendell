#include "OpenGLTexture2D.h"

namespace rendell
{
	OpenGLTexture2D::OpenGLTexture2D(uint32_t width, uint32_t height, TextureFormat format, const uint8_t* pixels) :
		Texture2D(width, height, format, pixels)
	{
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

		glGenTextures(1, &_textureId);
		glBindTexture(GL_TEXTURE_2D, _textureId);
		const GLint internalFormat = convertTextureFormatToInternalFormat(_format);
		glTexImage2D(
			GL_TEXTURE_2D,
			0,
			internalFormat,
			static_cast<GLsizei>(_width),
			static_cast<GLsizei>(_height),
			0,
			internalFormat,
			GL_UNSIGNED_BYTE,
			static_cast<const void*>(_pixels)
		);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	}

	OpenGLTexture2D::~OpenGLTexture2D()
	{
		glDeleteTextures(1, &_textureId);
	}

	void OpenGLTexture2D::bind(uint32_t textureBlock) const
	{
		_textureBlock = textureBlock;
		glActiveTexture(GL_TEXTURE0 + _textureBlock);
		glBindTexture(GL_TEXTURE_2D, _textureId);
	}

	void OpenGLTexture2D::unbind() const
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}

}