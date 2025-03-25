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
		void setSubTextureData(uint32_t index, uint32_t width, uint32_t height, const uint8_t* pixels) override;
		void bind(uint32_t textureBlock = 0) const override;
		void unbind() const override;

	private:
		GLuint _id;
		mutable uint32_t _textureBlock{ 0 };

	};

	RENDELL_DECLARE_SHARED_PTR_FACTORY(OpenGLTexture2DArray)
}