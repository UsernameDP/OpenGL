#include "glpch.hpp"
#include "Application.hpp"

namespace GLCore {
	Application::Application(const std::string& name, uint32_t width, uint32_t height, glm::vec4 backgroundColor){
		if (s_Instance) { //if there already is another instance
			THROW_RUNTIME_ERROR("There already is an instance of Application");
		}

		s_Instance = this;
		m_Window = new Window(WindowProps(name, width, height, backgroundColor));
		m_Window->init();

		const GLubyte* glslVersionString = glGetString(GL_SHADING_LANGUAGE_VERSION);
	}
	Application::~Application() {
		LOG("Application Destructor Emitted");
		destroy();
	}
	void Application::destroy() {
		LOG("Application destroyed");

		m_LayerStack.destroy();
		if (m_ImGuiLayer) m_ImGuiLayer->onDetach();
		m_Window->destroy();

		extraDestroy();
	}
	void Application::manualDestroy() {
		LOG("Application manually Destroyed");
		destroy();
		delete this;
	}

	void Application::run() {
		float currentTime;
		float lastFrameTime = 0.0f;

		TimeStep timeStep;
		while (m_Window->running()) {
			currentTime = (float)glfwGetTime();
			timeStep.setTime(currentTime);

			m_Window->onUpdate();

			for (Layer* layer : m_LayerStack)
				layer->onUpdate(timeStep);

			if (m_ImGuiLayer) {
				m_ImGuiLayer->begin();
				m_ImGuiLayer->onUpdate(timeStep);
				for (Layer* layer : m_LayerStack)
					layer->onImguiUpdate(timeStep);
				m_ImGuiLayer->end();
			}

			glfwSwapBuffers(Application::getGLFWWindow());
		}
	}
	
	void Application::pushLayer(Layer* layer) {
		m_LayerStack.pushLayer(layer);
	}
	void Application::popLayer(Layer* layer) {
		popLayer(layer);
	}
	void Application::setImGuiLayer(ImGuiLayer* layer) {
		m_ImGuiLayer = layer;
		m_ImGuiLayer->onAttach();
	}

	bool Application::getKey(uint16_t GLFW_KEY_, bool return_false_if_any_imgui_windowIsFocused) {
		bool isKeyDown = ImGui::GetIO().KeysDown[GLFW_KEY_];
		if (return_false_if_any_imgui_windowIsFocused) {
			if (ImGui::IsWindowFocused(ImGuiFocusedFlags_AnyWindow)) {
				return false;
			}
		}

		return isKeyDown;
	}

	//Virtual / Overrideable functions
	void Application::init() {};
	void Application::extraDestroy() {};

	Application* Application::s_Instance = nullptr;
}