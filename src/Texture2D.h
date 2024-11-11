#pragma once
#include <iostream>
#include <vector>
#include "TextureFormat.h"

namespace rendell
{
	class Texture2D
	{
	protected:
		Texture2D(uint32_t width, uint32_t height, TextureFormat format, const uint8_t* pixels);

	public:
		virtual void bind() const = 0;
		virtual void unbind() const = 0;

		uint32_t getWidth() const;
		uint32_t getHeight() const;
		TextureFormat getFormat() const;
		const uint8_t* getPixels() const;

	protected:
		uint32_t _width;
		uint32_t _height;
		TextureFormat _format;
		const uint8_t* _pixels;
	};
}