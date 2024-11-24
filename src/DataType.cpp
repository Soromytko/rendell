#include "DataType.h"
#define INT_SIZE 4
#define FLOAT_SIZE 4

namespace rendell
{
	uint32_t getSizeByType(DataType type)
	{
		switch (type)
		{
		case DataType::int1: return INT_SIZE * 1;
		case DataType::int2: return INT_SIZE * 2;
		case DataType::int3: return INT_SIZE * 3;
		case DataType::int4: return INT_SIZE * 4;
		case DataType::float1: return FLOAT_SIZE * 1;
		case DataType::float2: return FLOAT_SIZE * 2;
		case DataType::float3: return FLOAT_SIZE * 3;
		case DataType::float4: return FLOAT_SIZE * 4;
		}
	}
}