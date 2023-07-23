#pragma once
#include "Core.hpp"
#include <glm/vec4.hpp>
#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace GLCore {
	struct WindowProps {
		std::string title;
		uint32_t width;
		uint32_t height;
		glm::vec4 backgroundColor;

		WindowProps(const std::string& title, 
			uint32_t width, 
			uint32_t height,
			glm::vec4 backgroundColor) {
			this->title = title;
			this->width = width;
			this->height = height;
			this->backgroundColor = backgroundColor;
		}
	};

	class Window {
	private:
		std::string title;
		uint32_t width;
		uint32_t height;
		glm::vec4 backgroundColor;

		GLFWwindow* glfwWindow;
	public:
		Window() = default;
		Window(const WindowProps& props);
		~Window();

		static std::unique_ptr<Window> create(const WindowProps& props);

		void init();
		void onUpdate();
		
		inline bool running() { return !glfwWindowShouldClose(glfwWindow); }
		inline GLFWwindow*& getGLFWWindow() { return glfwWindow; }
		inline uint32_t  getWidth() { return width; }
		inline uint32_t  getHeight() { return height; }
	};
}