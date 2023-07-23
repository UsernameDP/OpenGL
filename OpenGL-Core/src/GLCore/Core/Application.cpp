#include "glpch.hpp"
#include "Application.hpp"

namespace GLCore {
	Application::Application(const std::string& name, uint32_t width, uint32_t height, glm::vec4 backgroundColor) {
		if (s_Instance) { //if there already is another instance
			THROW_RUNTIME_ERROR("There already is an instance of Application");
		}

		s_Instance = this;

		const GLubyte* glslVersionString = glGetString(GL_SHADING_LANGUAGE_VERSION);
		std::cout << glslVersionString;

		m_Window = Window::create(WindowProps(name, width, height, backgroundColor));
		init();
	}
	
	void Application::pushLayer(Layer* layer) {
		layerStack.pushLayer(layer);
	}
	void Application::popLayer(Layer* layer) {
		popLayer(layer);
	}

	void Application::run() {
		float currentTime;
		float lastFrameTime = 0.0f;

		TimeStep timeStep;
		while (m_Window->running()) {
			currentTime = (float)glfwGetTime();
			timeStep.setTime(currentTime);

			m_Window->onUpdate();
			for (Layer* layer : layerStack)
				layer->onUpdate(timeStep);

		}
	}

	Application* Application::s_Instance = nullptr;
	std::unique_ptr<Window> m_Window = nullptr;
	const std::string& glslVersion = NULL;
}