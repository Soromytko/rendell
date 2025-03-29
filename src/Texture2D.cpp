#include <rendell/Texture2D.h>

namespace rendell
{
	Texture2D::Texture2D(uint32_t width, uint32_t height, TextureFormat format, const uint8_t* pixels) :
		_width(width), _height(height), _format(format), _pixels(pixels)
	{
	}

	uint32_t Texture2D::getWidth() const
	{
		return _width;
	}

	uint32_t Texture2D::getHeight() const
	{
		return _height;
	}

	TextureFormat Texture2D::getFormat() const
	{
		return _format;
	}

	const uint8_t* Texture2D::getPixels() const
	{
		return _pixels;
	}

}
