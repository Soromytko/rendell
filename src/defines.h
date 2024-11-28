#pragma once

namespace rendell
{
	enum class SpecificationAPI
	{
		OpenGL,
	};

	enum BufferBit : uint32_t
	{
		colorBufferBit = 1,
		depthBufferBit,
	};

	struct Initer
	{
		SpecificationAPI api = SpecificationAPI::OpenGL;
		void* context = nullptr;
	};
	
}
