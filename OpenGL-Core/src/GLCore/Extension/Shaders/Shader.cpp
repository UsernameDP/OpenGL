#include "glpch.hpp"
#include "Shader.hpp"

namespace GLCore::Shaders {
	Shader::~Shader() {
		glDeleteProgram(programID);

		extraDestructor();
	}

	void Shader::use() {
		glUseProgram(programID);
	}
	void Shader::detach() {
		glUseProgram(0);
	}
	
	
	void Shader::extraDestructor() {};
	void Shader::compile()  {};
}