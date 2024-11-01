#include "OpenGLTexture2D.h"

namespace rendell
{
	static GLint convertToInternalFormat(TextureFormat format)
	{
		switch (format)
		{
		case TextureFormat::R: return GL_RED;
		case TextureFormat::RG: return GL_RG;
		case TextureFormat::RGB: return GL_RGB;
		case TextureFormat::BGR: return GL_BGR;
		case TextureFormat::RGBA: return GL_RGBA;
		case TextureFormat::BGRA: return GL_BGRA;
		case TextureFormat::R_INT: return GL_RED_INTEGER;
		case TextureFormat::RG_INT: return GL_RG_INTEGER;
		case TextureFormat::RGB_INT: return GL_RGB_INTEGER;
		case TextureFormat::BGR_INT: return GL_BGR_INTEGER;
		case TextureFormat::RGBA_INT: return GL_RGBA_INTEGER;
		case TextureFormat::BGRA_INT: return GL_BGRA_INTEGER;
		}
		return 0;
	}

	OpenGLTexture2D::OpenGLTexture2D(uint32_t width, uint32_t height, TextureFormat format, const uint8_t* pixels) :
		Texture2D(width, height, format, pixels)
	{
		glGenTextures(1, &_textureId);
		glBindTexture(GL_TEXTURE_2D, _textureId);
		const GLint internalFormat = convertToInternalFormat(_format);
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

	void OpenGLTexture2D::bind() const
	{
		glBindTexture(GL_TEXTURE_2D, _textureId);
	}

	void OpenGLTexture2D::unbind() const
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}