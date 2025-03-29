#pragma once
#include <cstdint>

#define RENDELL_DECLARE_SHARED_PTR(ClassName) \
	typedef std::shared_ptr<ClassName> ClassName##SharedPtr;

#define RENDELL_DECLARE_SHARED_PTR_FACTORY(ClassName) \
	RENDELL_DECLARE_SHARED_PTR(ClassName) \
	template <typename... Args> \
    ClassName##SharedPtr make##ClassName(Args&&... args) { \
		return std::make_shared<ClassName>(std::forward<Args>(args)...); \
    }

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
		void* nativeWindowHandle = nullptr;
		void* x11Display = nullptr;
	};
}
