#pragma once
#include <memory>
#include <string>
#include <vector>

namespace rendell {
using IndexBufferData = std::vector<uint32_t>;
using VertexBufferData = std::vector<float>;
using ShaderSrcData = std::string;

enum class UniformType {
	vec2, vec3, vec4,
};
} // namespace rendell
