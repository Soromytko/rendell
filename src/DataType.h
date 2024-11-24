#pragma once
#include <stdint.h>

namespace
{
	enum class DataType
	{
		int1, int2, int3, int4,
		float1, float2, float3, float4,

	};

	uint32_t getSizeByDataType(DataType type);
}