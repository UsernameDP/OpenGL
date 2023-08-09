#include "pch.hpp"
#include "Shader.hpp"
#include "GLCore/Extension/util/AssetPool.hpp"

namespace GLCore::Shaders {
	PrimitiveShader::PrimitiveShader(const GLenum& SHADER_TYPE, const std::string& GLSL_PATH) {
		this->SHADER_TYPE = SHADER_TYPE;
		this->GLSL_PATH = GLSL_PATH;
		this->GLSL_SRC = util::AssetPool::getGLSLSrc(GLSL_PATH);
	};


	Shader::Shader(const std::string& name) : m_name(name) {};
	Shader::~Shader() {
		glDeleteProgram(programID);
		for (PrimitiveShader* p : PrimitiveShaders) {
			delete p;
		}

		extraDestructor();
	}
	void Shader::extraDestructor() {
		//still need to define this despite {} since the function is being called in baseclass 
	};

	void Shader::addPrimitiveShader(const GLenum& SHADER_TYPE, const std::string& GLSL_PATH) {
		PrimitiveShaders.push_back(new PrimitiveShader(SHADER_TYPE, GLSL_PATH));
	}

	void Shader::compile() {
		//Compile PrimitiveShaders
		for (PrimitiveShader* p : PrimitiveShaders) {
			const char* SHADER_SRC_C = p->GLSL_SRC->c_str();

			if (p->GLSL_SRC->empty()) THROW_RUNTIME_ERROR(p->GLSL_PATH + "\t is empty");

			p->shaderID = glCreateShader(p->SHADER_TYPE);
			glShaderSource(p->shaderID, 1, &SHADER_SRC_C, NULL);
			glCompileShader(p->shaderID);
			checkShaderSuccess(p->GLSL_PATH, p->shaderID);
		}

		//Link Program
		programID = glCreateProgram();
		for (PrimitiveShader* p : PrimitiveShaders) {
			glAttachShader(programID, p->shaderID);
		}
		glLinkProgram(programID);
		checkProgramSuccess(programID);

		//Delete PrimitiveShader IDS
		for (PrimitiveShader* p : PrimitiveShaders) {
			glDeleteShader(p->shaderID);
		}
	}
	void Shader::use() {
		glUseProgram(programID);
	}
	void Shader::detach() {
		glUseProgram(0);
	}
	
	/*All uniform uploads*/
	//Floats
	void Shader::uploadFloat(const std::string& name, const float& value) {
		int location = glGetUniformLocation(programID, name.c_str());
		use();
		glUniform1f(location, value);
	}
	void Shader::uploadMat4f(const std::string& name, const glm::mat4& value) {
		int location = glGetUniformLocation(programID, name.c_str());
		use();
		glUniformMatrix4fv(location, 1, GL_FALSE, &value[0][0]);
	}
	

	//ints
	void Shader::uploadInt(const std::string& name, const int& value) {
		int location = glGetUniformLocation(programID, name.c_str());
		use();
		glUniform1i(location, value);
	}
}