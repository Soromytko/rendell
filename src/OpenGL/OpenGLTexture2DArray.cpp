#include "OpenGLTexture2DArray.h"

namespace rendell
{
	OpenGLTexture2DArray::OpenGLTexture2DArray(uint32_t width, uint32_t height, uint32_t count, TextureFormat format) :
		Texture2DArray(width, height, count, format), _internalFormat(convertTextureFormatToInternalFormat(format))
	{
		glCreateTextures(GL_TEXTURE_2D_ARRAY, 1, &_id);
		glTextureStorage3D(
			_id,
			0,
			_internalFormat,
			static_cast<GLsizei>(_width),
			static_cast<GLsizei>(_height),
			static_cast<GLsizei>(_count)
		);

		glBindTexture(GL_TEXTURE_2D_ARRAY, _id);
		glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glBindTexture(GL_TEXTURE_2D_ARRAY, 0);
	}

	OpenGLTexture2DArray::~OpenGLTexture2DArray()
	{
		glDeleteTextures(1, &_id);
	}

	void OpenGLTexture2DArray::setSubTextureData(uint32_t index, const uint8_t* pixels)
	{
		glTextureSubImage3D(
			_id,
			0,
			0,
			0,
			static_cast<GLint>(index),
			static_cast<GLint>(_width),
			static_cast<GLint>(_height),
			static_cast<GLint>(_count),
			_internalFormat,
			GL_UNSIGNED_BYTE,
			static_cast<const void*>(pixels)
		);
	}

	void OpenGLTexture2DArray::bind() const
	{
		glBindTexture(GL_TEXTURE_2D_ARRAY, _id);
	}

	void OpenGLTexture2DArray::unbind() const
	{
		glBindTexture(GL_TEXTURE_2D_ARRAY, 0);
	}

}
