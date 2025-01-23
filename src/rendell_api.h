#pragma once

#ifdef RENDELL_BUILD_DLL
#ifdef _WIN32
#define RENDELL_API __declspec(dllexport)
#else
#define RENDELL_API __attribute__((visibility("default")))
#endif
#else
#define RENDELL_API
#endif
