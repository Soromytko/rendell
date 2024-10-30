#pragma once
#include <vector>

namespace rendell
{
	class IndexBuffer
	{
	protected:
		IndexBuffer(std::vector<uint32_t>&& indices);

	public:
		virtual void bind() const = 0;
		virtual void unbind() const = 0;
		const std::vector<uint32_t>& getIndices() const;

	protected:
		std::vector<uint32_t> _indices;

	};
}