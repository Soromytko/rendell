#include "IndexBuffer.h"
#include "OpenGL/OpenGLIndexBuffer.h"
#include "Renderer.h"

using namespace rendell;

IndexBuffer::IndexBuffer(std::vector<uint32_t>&& indices)
{
	_indices = std::move(indices);
}
