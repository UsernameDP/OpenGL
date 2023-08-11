#pragma once
#include "../Extension.hpp"

namespace GLCore::Shaders {
	static void checkShaderSuccess(const std::string& shaderPath, GLuint& shaderID) {
		int  success;
		char infoLog[512];
		glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(shaderID, 512, NULL, infoLog);
			std::string message = "SHADER COMPILATION FAILED " + shaderPath + "\n" +
				"InfoLog : " + infoLog;

			THROW_RUNTIME_ERROR(message);
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

			THROW_RUNTIME_ERROR(message);
		}
	}

	struct PrimitiveShader {
		GLuint shaderID;
		GLenum SHADER_TYPE;
		std::string GLSL_PATH;
		std::string* GLSL_SRC;

		PrimitiveShader(const GLenum& SHADER_TYPE, const std::string& GLSL_PATH);
	};

	class Shader {
	private:
		std::string m_name;
		std::vector<PrimitiveShader*> PrimitiveShaders;
	protected:
		GLuint programID = 0;
	public:
		Shader(const std::string& name);
		~Shader();
		virtual void extraDestructor() = 0;
		
		void addPrimitiveShader(const GLenum& SHADER_TYPE, const std::string& GLSL_PATH);

		void compile();
		void use();
		void detach();

		inline std::string& getName() { return m_name; }
	public: //All the uniform uploads

		void uploadFloat(const std::string& name, const float& value);
		void uploadMat4f(const std::string& name, const glm::mat4& value);

		void uploadInt(const std::string& name, const int& value);
		void uploadTexture(const std::string& name, const unsigned int& slot);

	};
}