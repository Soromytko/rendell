#include <rendell/Texture2DArray.h>

namespace rendell
{
	Texture2DArray::Texture2DArray(uint32_t width, uint32_t height, uint32_t count, TextureFormat format) :
		_width(width), _height(height), _count(count), _format(format)
	{

	}

	uint32_t Texture2DArray::getWidth() const
	{
		return _width;
	}

	uint32_t Texture2DArray::getHeight() const
	{
		return _height;
	}

	uint32_t Texture2DArray::getCount() const
	{
		return _count;
	}

	TextureFormat Texture2DArray::getFormat() const
	{
		return _format;
	}
}