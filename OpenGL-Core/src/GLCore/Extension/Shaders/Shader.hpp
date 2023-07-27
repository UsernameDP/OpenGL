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

	class Shader {
	private:
		std::string m_name;
	protected:
		GLuint programID = 0;
	public:
		Shader(const std::string& name) : m_name(name) {};
		~Shader();
		virtual void extraDestructor(); //LOG_DESTRUCTOR here

		virtual void compile();
		void use();
		void detach();

		inline std::string& getName() { return m_name; }
	public: //All the uniform uploads


	};
}