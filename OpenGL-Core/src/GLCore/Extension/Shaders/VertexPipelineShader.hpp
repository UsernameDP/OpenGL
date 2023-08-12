#pragma once
#include "../Extension.hpp"
#include "Shader.hpp"

namespace GLCore::Shaders {
	class VertexPipelineShader : public Shader {
	private:
		std::string vertShaderPath;
		std::string fragShaderPath;

		std::string* vertShaderSrc = nullptr;
		std::string* fragShaderSrc = nullptr;
	public:
		VertexPipelineShader(const std::string& name, const std::string& vertPath, const std::string& fragPath);
	};
}