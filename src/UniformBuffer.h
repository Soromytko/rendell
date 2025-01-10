#pragma once
#include <cstdint>
#include <memory>

namespace rendell
{
	class UniformBuffer
	{
	protected:
		UniformBuffer(const void* data, size_t size);

	public:
		virtual void bind(uint32_t binding = 0) const = 0;
		virtual void unbind() const = 0;
		virtual void setSubData(const void* data, size_t size, size_t offset = 0) const = 0;

		const void* getData() const;
		size_t getSize() const;

	protected:
		const void* _data;
		const size_t _size;
	};

	typedef std::shared_ptr<UniformBuffer> UniformBufferSharedPtr;
}