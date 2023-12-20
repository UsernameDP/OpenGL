// Shader in takes an ArrayList of src and ShaderType
#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>

namespace GLCore::Extension::Shaders {
	static void checkShaderSuccess(const std::string& shaderPath, GLuint& shaderID) {
		int  success;
		char infoLog[512];
		glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(shaderID, 512, NULL, infoLog);
			std::string message = "SHADER COMPILATION FAILED " + shaderPath + "\n" +
				"InfoLog : " + infoLog;

			LOG_ERROR(message);
		}
	}
	static void checkProgramSuccess(GLuint& programID) {
		int  success;
		char infoLog[512];
		glGetProgramiv(programID, GL_LINK_STATUS, &success);

		if (!success) {
			glGetProgramInfoLog(programID, 512, NULL, infoLog);
			std::string message = std::string("SHADER_PROGRAM LINKING FAILED ") + "\n" +
				"InfoLog : " + infoLog;

			LOG_ERROR(message);
		}
	}

	struct PrimitiveShader {
		GLuint shaderID;
		GLenum SHADER_TYPE;
		std::string GLSL_PATH;
		std::string* GLSL_SRC;

		PrimitiveShader(const GLenum& SHADER_TYPE, const std::string& GLSL_PATH);
		~PrimitiveShader();
	};

	class Shader {
	private:
		std::string name;
		std::vector<PrimitiveShader*> PrimitiveShaders;
	protected:
		GLuint programID = 0;
		inline const GLuint& getProgramID() { return this->programID; }
	public:
		Shader(const std::string& name);
		virtual ~Shader();

		void addPrimitiveShader(const GLenum& SHADER_TYPE, const std::string& GLSL_PATH);

		void compile();
		void use();
		void detach();
		void destroy();

		inline std::string& getName() { return this->name; }
	public:
		//Strict requires that the uniform makes an impact on the final color
		//The order you upload uniforms MATTER!! Make sure to upload .vert uniforms BEFORE .frag!!
		int GetUniformLocation(const std::string& name, const bool& strict = false);

		void uploadFloat(const std::string& name, const float& value, const bool& strict = false);
		void uploadMat4f(const std::string& name, const glm::mat4& value, const bool& strict = false);

		void uploadInt(const std::string& name, const int& value, const bool& strict = false);
		void uploadTexture(const std::string& name, const unsigned int& slot, const bool& strict = false);

	};
}