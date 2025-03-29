#include "context_creation.h"
#include "IContext.h"

namespace rendell
{
	IContextSharedPtr createContext(const Initer& initer)
	{
		switch (initer.api)
		{
		case SpecificationAPI::OpenGL: return createOpenGLContext(initer);
		}
		return nullptr;
	}

	OpenGLContextSharedPtr createOpenGLContext(const Initer& initer)
	{
#if defined(_WIN32)
		return makeWindowsOpenGLContext(initer);
#elif defined(__linux__)
		return makeLinuxOpenGLContext(initer);
#endif
		return nullptr;
	}
}