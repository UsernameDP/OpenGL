#include "pch.hpp"
#include <GLFW/glfw3.h>
#include "GLCore/Core/Window.hpp"

namespace GLCore {
	void INIT_GLFW() {
		if (!glfwInit()) {
			LOG_ERROR("GLFW didn't initialize properly");
		}
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef APPLE
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
	}

	WindowProps::WindowProps(const std::string& title,
		uint32_t width,
		uint32_t height,
		const glm::vec4& backgroundColor
	) : title(title),
		width(width),
		height(height),
		backgroundColor(backgroundColor){};

	Window::Window(const WindowProps& props) : props(props) {}

	Window::~Window() {
		glfwDestroyWindow(GLFWWindow);
		glfwTerminate();
	}

	void Window::init() {
		GLFWWindow = glfwCreateWindow(props.width, props.height, props.title.c_str(), NULL, NULL);
	}

}
