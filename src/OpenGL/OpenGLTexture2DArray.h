#pragma once
#include "../Texture2DArray.h"
#include "OpenGLUtils.h"

namespace rendell
{
	class OpenGLTexture2DArray final : public Texture2DArray
	{
	public:
		OpenGLTexture2DArray(uint32_t width, uint32_t height, uint32_t count, TextureFormat format);
		~OpenGLTexture2DArray();
		void setSubTextureData(uint32_t index, const uint8_t* pixels) override;
		void bind() const override;
		void unbind() const override;

	private:
		GLint _internalFormat;
		GLuint _id;

	};
}