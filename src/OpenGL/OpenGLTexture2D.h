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

		void bind(uint32_t textureBlock = 0) const override;
		void unbind() const override;

	private:
		GLuint _textureId{};
		mutable uint32_t _textureBlock{ 0 };

	};

	RENDELL_DECLARE_SHARED_PTR_FACTORY(OpenGLTexture2D)
}