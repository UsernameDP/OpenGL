#include "pch.hpp"
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include "GLCore/Core/Window.hpp"

namespace GLCore
{
	static void initViewPort(const int width, const int height)
	{
		glViewport(0, 0, width, height);
	}
	static void framebuffer_size_callback(GLFWwindow *window, int width, int height)
	{
		glViewport(0, 0, width, height);
	}
	static void glfw_error_callback(int error, const char *description)
	{
		fprintf(stderr, "Error : %s\n", description);
	}

	void INIT_GLFW()
	{
		if (!glfwInit())
		{
			LOG_ERROR("GLFW didn't initialize properly");
		}
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef APPLE
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
		glfwSetErrorCallback((GLFWerrorfun)glfw_error_callback);

		LOG_INFO("GLFW initialized");
	}
	void INIT_GLAD()
	{
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			LOG_ERROR("Failed to initialize GLAD");
		}

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_DEPTH_TEST);

		LOG_INFO("GLAD initialized");
	}

	WindowProps::WindowProps(const std::string &name,
							 uint32_t width,
							 uint32_t height,
							 const glm::vec4 &backgroundColor) : name(name),
																 width(width),
																 height(height),
																 backgroundColor(backgroundColor){};

	Window::Window(const WindowProps &props) : props(props) {}

	Window::~Window()
	{
		glfwDestroyWindow(GLFWWindow);
		glfwTerminate();
	}

	void Window::init()
	{
		static bool firstWindowInstance = true;

		//-------------------------------------------------------------
		if (firstWindowInstance)
		{
			INIT_GLFW();
		}
		//-------------------------------------------------------------

		GLFWWindow = glfwCreateWindow(props.width, props.height, props.name.c_str(), NULL, NULL);

		if (GLFWWindow == NULL)
		{
			LOG_ERROR("Failed to create GLFW window");
		}
		glfwMakeContextCurrent(GLFWWindow);
		glfwSwapInterval(1);

		INIT_GLAD();

		initViewPort((int)props.width, (int)props.height);
		glfwSetFramebufferSizeCallback(GLFWWindow, (GLFWframebuffersizefun)framebuffer_size_callback);

		firstWindowInstance = false;
	}

	void Window::onUpdate()
	{
		glfwPollEvents();
		glClearColor(props.backgroundColor.r, props.backgroundColor.g, props.backgroundColor.b, props.backgroundColor.a);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

}
