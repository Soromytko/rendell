#pragma once
#include <memory>
#include <rendell/private/defines.h>
#include "Specification.h"

namespace rendell
{
	class IContext
	{
	protected:
		IContext() = default;

	public:
		~IContext() = default;

		virtual Specification* getSpecification() const = 0;
		virtual std::string getName() const = 0;
		virtual bool isInitialized() const = 0;
		virtual bool makeCurrent() = 0;
		virtual bool swapBuffers() = 0;

	};

	RENDELL_DECLARE_SHARED_PTR(IContext)

}