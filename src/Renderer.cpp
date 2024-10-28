#pragma once
#include <glad/glad.h>
#include "Renderer.h"

using namespace rendell;

Renderer::Api Renderer::getApi()
{
	return  _api;
}

void Renderer::setApi(Api api)
{
	_api = api;
}

bool Renderer::init(std::string *reason)
{
	char* reasonPtr = nullptr;
	if (!initApi())
	{
		reasonPtr = "Failed to initialize GLAD";
	} 
	
	if (reasonPtr)
	{
		if (reason)
		{
			*reason = reasonPtr;
		}
		return false;
	}
	return true;
}

bool Renderer::initApi()
{
	//return gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	return false;
}

Renderer::Api Renderer::_api{ Api::OpenGL };

