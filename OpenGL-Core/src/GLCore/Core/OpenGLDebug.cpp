#include "pch.hpp"
#include "OpenGLDebug.hpp"

namespace GLCore {
	static DebugLogLevel s_DebugLogLevel = DebugLogLevel::HighAssert;

	void SetGLDebugLogLevel(DebugLogLevel level)
	{
		s_DebugLogLevel = level;
	}

	void openGLDebugCallBack(GLenum source,
		GLenum type,
		GLuint id,
		GLenum severity,
		GLsizei length,
		const GLchar* message,
		const void* userParam) {

		switch (severity)
		{
		case GL_DEBUG_SEVERITY_HIGH:
			if ((int)s_DebugLogLevel > 0)
			{
				THROW_RUNTIME_ERROR("[OpenGL Debug HIGH] {0}" + std::string(message));
			}
			break;
		case GL_DEBUG_SEVERITY_MEDIUM:
			if ((int)s_DebugLogLevel > 2)
				WARNING("[OpenGL Debug MEDIUM] {0}", +std::string(message));
			break;
		case GL_DEBUG_SEVERITY_LOW:
			if ((int)s_DebugLogLevel > 3)
				LOG("[OpenGL Debug LOW] {0}", +std::string(message));
			break;
		case GL_DEBUG_SEVERITY_NOTIFICATION:
			if ((int)s_DebugLogLevel > 4)
				LOG("[OpenGL Debug NOTIFICATION] {0}", +std::string(message));
			break;
		}
	}

	void enableGLDebugging() {
		glEnable(GL_DEBUG_OUTPUT);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		glDebugMessageCallback(openGLDebugCallBack, nullptr);

		LOG("OpenGL Debugging ENABLED");
	}
}