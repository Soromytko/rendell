#pragma once
#include "../Texture2D.h"
#include "OpenGLUtils.h"

namespace rendell
{
	class OpenGLTexture2D final : public Texture2D
	{
	public:
		OpenGLTexture2D(uint32_t width, uint32_t height, TextureFormat format, const uint8_t* pixels);
		~OpenGLTexture2D();

		void bind() const override;
		void unbind() const override;

	private:
		GLuint _textureId{};

	};
}