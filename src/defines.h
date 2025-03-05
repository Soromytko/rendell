#pragma once
#include <cstdint>

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

#define DECLARE_SHARED_PTR(ClassName) \
	typedef std::shared_ptr<ClassName> ClassName##SharedPtr;

#define DECLARE_SHARED_PTR_FACTORY(ClassName) \
	DECLARE_SHARED_PTR(ClassName) \
	template <typename... Args> \
    ClassName##SharedPtr make##ClassName(Args&&... args) { \
		return std::make_shared<ClassName>(std::forward<Args>(args)...); \
    }
	
}
