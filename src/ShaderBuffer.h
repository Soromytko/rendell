#pragma once
#include <iostream>
#include <memory>
#include "defines.h"

namespace rendell
{
	class ShaderBuffer
	{
	protected:
		ShaderBuffer(const void* data, size_t size);

	public:
		virtual void bind(uint32_t binding = 0) const = 0;
		virtual void unbind() const = 0;
		const void* getData() const;
		size_t getSize() const;

		virtual void setSubData(const void* data, size_t size, size_t offset = 0) = 0;

	protected:
		const void* _data;
		size_t _size;
	};

	RENDELL_DECLARE_SHARED_PTR_FACTORY(ShaderBuffer)
}