#pragma once
#include <string>
#include <vector>
#include "DataType.h"

namespace rendell
{
	class VertexBufferLayout
	{
	public:
		VertexBufferLayout(DataType type, bool normalized = false, uint32_t offset = 0);
		DataType getType() const;
		uint32_t getSize() const;
		uint32_t getOffset() const;
		bool getNormalized() const;
		int getComponentCountByShaderType() const;
		void setOffset(uint32_t value);

	private:
		DataType _type;
		//std::string name;
		uint32_t _size;
		uint32_t _offset;
		bool _normalized;

	};
}
