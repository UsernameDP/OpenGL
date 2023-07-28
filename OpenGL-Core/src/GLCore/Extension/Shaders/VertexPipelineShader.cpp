#include "glpch.hpp"
#include "VertexPipelineShader.hpp"

namespace GLCore::Shaders {
	VertexPipelineShader::VertexPipelineShader(
		const std::string& name, 
		const std::string& vertPath, 
		const std::string& fragPath) : Shader(name)
	{ 
		addPrimitiveShader(GL_VERTEX_SHADER, vertPath);
		addPrimitiveShader(GL_FRAGMENT_SHADER, fragPath);

		compile();

		LOG_CONSTRUCTOR("VertexPipelineShader<name:" + getName() + ">");
	}

	void VertexPipelineShader::extraDestructor() {
		LOG_DESTRUCTOR("VertexPipelineShader<name:" + getName() + ">");
	}
}