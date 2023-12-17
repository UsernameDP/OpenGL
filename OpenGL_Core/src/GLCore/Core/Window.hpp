#pragma once

#include <glm/glm.hpp>

namespace GLCore {
	void INIT_GLFW();

	struct WindowProps {
		std::string title;
		uint32_t width;
		uint32_t height;
		glm::vec4 backgroundColor;

		WindowProps( const std::string& title, 
			uint32_t width, 
			uint32_t height,
			const glm::vec4& backgroundColor
		);
	};

	class Window {
	private:
		WindowProps props; 
		GLFWwindow* GLFWWindow;
	public:
		Window(const WindowProps& props);
		~Window();

		void init();
		void onUpdate();

		inline GLFWwindow* getGLFWWindow() { return GLFWWindow; }
		inline const std::string& getTitle() { return props.title; }
		inline const uint32_t& getWidth() { return props.width; }
		inline const uint32_t& getHeight() { return props.height; }
	};
}