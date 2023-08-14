#include "pch.hpp"
#include "ComputeShader.hpp"

namespace GLCore::Shaders {

	ComputeShader::ComputeShader(const std::string& name, const std::string& computePath)
		: Shader(name) {

		addPrimitiveShader(GL_COMPUTE_SHADER, computePath);
		compile();
	}
}