#pragma once
#include <glad/glad.h>
#include "../TextureFormat.h"

namespace rendell
{
	GLint convertTextureFormatToBaseFormat(TextureFormat format);
	GLint convertTextureFormatToSizedFormat(TextureFormat format);

}