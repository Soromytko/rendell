#pragma once
#include <glad/glad.h>
#include "../TextureFormat.h"

namespace rendell
{
	GLint convertTextureFormatToInternalFormat(TextureFormat format);

}