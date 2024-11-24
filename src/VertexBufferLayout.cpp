#include "VertexBufferLayout.h"

namespace rendell
{
	VertexBufferLayout::VertexBufferLayout(DataType type, bool normalized, uint32_t offset) :
		_type(type), _normalized(normalized), _offset(offset)
	{
		_size = getSizeByDataType(type);
	}

	DataType VertexBufferLayout::getType() const
	{
		return _type;
	}

	uint32_t VertexBufferLayout::getSize() const
	{
		return _size;
	}

	uint32_t VertexBufferLayout::getOffset() const
	{
		return _offset;
	}

	bool VertexBufferLayout::getNormalized() const
	{
		return _normalized;
	}

	int VertexBufferLayout::getComponentCountByShaderType() const
	{
		switch (_type)
		{
		case DataType::int1: case DataType::float1: return 1;
		case DataType::int2: case DataType::float2: return 2;
		case DataType::int3: case DataType::float3: return 3;
		case DataType::int4: case DataType::float4: return 4;
		}
		return 0;
	}

	void VertexBufferLayout::setOffset(uint32_t value)
	{
		_offset = value;
	}
}
