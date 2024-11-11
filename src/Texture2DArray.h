#pragma once
#include <iostream>
#include <vector>
#include "TextureFormat.h"

namespace rendell
{
	class Texture2DArray
	{
	protected:
		Texture2DArray(uint32_t width, uint32_t height, uint32_t count, TextureFormat format);

	public:
		virtual void setSubTextureData(uint32_t index, const uint8_t *pixels) = 0;
		virtual void bind() const = 0;
		virtual void unbind() const = 0;

		uint32_t getWidth() const;
		uint32_t getHeight() const;
		uint32_t getCount() const;
		TextureFormat getFormat() const;

	protected:
		uint32_t _width;
		uint32_t _height;
		uint32_t _count;
		TextureFormat _format;
	};
}