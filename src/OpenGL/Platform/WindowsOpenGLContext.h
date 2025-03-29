#pragma once
#include <Windows.h>
#include <rendell/private/defines.h>
#include "../../IContext.h"

namespace rendell
{
	class WindowsOpenGLContext : public IContext
	{
	public:
		WindowsOpenGLContext(const Initer& initer);
		~WindowsOpenGLContext();

		Specification* getSpecification() const override;
		std::string getName() const override;
		bool isInitialized() const override;
		bool makeCurrent() override;
		bool swapBuffers() override;

	private:
		bool createContext(int majorVersion, int minorVersion);
		bool releaseContext();
		bool init();

		HWND _hwnd = NULL;
		PIXELFORMATDESCRIPTOR _pfd{};
		HDC _hdc = NULL;
		HGLRC _hglrc = NULL;

		bool _isInitialized{ false };
	};

	RENDELL_DECLARE_SHARED_PTR_FACTORY(WindowsOpenGLContext)
}
