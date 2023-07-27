#include "glpch.hpp"
#include "VertexPipelineShader.hpp"

namespace GLCore::Shaders {
	VertexPipelineShader::VertexPipelineShader(
		const std::string& name, 
		const std::string& vertPath, 
		const std::string& fragPath) : 
		Shader(name), 
		vertShaderPath(vertPath) , 
		fragShaderPath(fragPath)
	{ 
		vertShaderSrc = Util::AssetPool::getGLSLSrc(vertPath);
		fragShaderSrc = Util::AssetPool::getGLSLSrc(fragPath);
	}

	void VertexPipelineShader::extraDestructor() {
		LOG_DESTRUCTOR("VertexPipelineShader<name:" + getName() + ">");
	}

	void VertexPipelineShader::compile() {
		GLuint vertexShaderID;
		GLuint fragmentShaderID;

		const char* vertShaderSrc_c = vertShaderSrc->c_str();

		vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShaderID, 1, &vertShaderSrc_c , NULL);
		glCompileShader(vertexShaderID);
		checkShaderSuccess(vertShaderPath, vertexShaderID);

		fragmentShaderID = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(fragmentShaderID, 1, &vertShaderSrc_c, NULL);
		glCompileShader(fragmentShaderID);
		checkShaderSuccess(vertShaderPath, fragmentShaderID);

		/*----------------------------------------------------------*/
		programID = glCreateProgram();
		glAttachShader(programID, vertexShaderID);
		glAttachShader(programID, fragmentShaderID);
		glLinkProgram(programID);
		checkProgramSuccess(programID);

		glDeleteShader(vertexShaderID);
		glDeleteShader(fragmentShaderID);
	}
}