#pragma once
#include <iostream>

namespace rendell
{
	class ShaderBuffer
	{
	protected:
		ShaderBuffer(const void* data, size_t size);

	public:
		virtual void bind(uint32_t layoutIndex = 0) const = 0;
		virtual void unbind() const = 0;
		const void* getData() const;
		size_t getSize() const;

		virtual void setSubData(const void* data, size_t offset, size_t size) = 0;

	protected:
		const void* _data;
		size_t _size;
	};
}