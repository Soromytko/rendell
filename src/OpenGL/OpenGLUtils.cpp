#include "OpenGLUtils.h"

namespace rendell
{
	GLint convertTextureFormatToInternalFormat(TextureFormat format)
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


}