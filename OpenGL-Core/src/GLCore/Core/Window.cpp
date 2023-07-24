#include "glpch.hpp"
#include "Window.hpp"
#include <GLFW/glfw3.h>

namespace GLCore {
	static void initGLFW() {
		if (!glfwInit()) {
			THROW_RUNTIME_ERROR("GLFW didn't intialize properly");
		}
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

		LOG_SUCCESS("GLFW Initialized");
	}
	static void initGLAD() {
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
			THROW_RUNTIME_ERROR("Failed to initialize GLAD");
		}
		LOG_SUCCESS("GLAD Initialized");
	}
	static void initViewPort(const int width, const int height)
	{
		glViewport(0, 0, width, height);
	}
	static void framebuffer_size_callback(GLFWwindow* window, int width, int height)
	{
		glViewport(0, 0, width, height);
	}
	static void error_callback(int error, const char* description)
	{
		fprintf(stderr, "Error : %s\n", description);
	}


	Window::Window(const WindowProps& props) {
		this->title = props.title;
		this->width = props.width;
		this->height = props.height;
		this->backgroundColor = props.backgroundColor;
		this->glfwWindow = nullptr;
	}

	void Window::destroy() {
		glfwDestroyWindow(glfwWindow);
		glfwTerminate();

		delete this;
	}

	void Window::init() {
		initGLFW();
		glfwSetErrorCallback((GLFWerrorfun)error_callback);

		glfwWindow = glfwCreateWindow((int)width, (int)height, title.c_str(), NULL, NULL);
		if (glfwWindow == NULL) {
			THROW_RUNTIME_ERROR("Failed to create GLFW window");
		}
		glfwMakeContextCurrent(glfwWindow);
		glfwSwapInterval(1); //Enable vsync
		

		initGLAD();
		
		initViewPort( (int) width,  (int) height);
		glfwSetFramebufferSizeCallback(glfwWindow, (GLFWframebuffersizefun)framebuffer_size_callback);

		LOG_SUCCESS("GLFWWindow Created & Configured");
	}
	void Window::onUpdate() {
		glfwPollEvents();
		glClearColor(backgroundColor.r, backgroundColor.g, backgroundColor.b, backgroundColor.a);
		glClear(GL_COLOR_BUFFER_BIT);
	}
}