#include "pch.hpp"
#include "Application.hpp"

namespace GLCore {
	static int getGLSLVersionInt() {
		// Get the OpenGL version string
		const char* versionStr = reinterpret_cast<const char*>(glGetString(GL_VERSION));

		// Extract the major and minor version numbers from the version string
		int majorVersion = 0;
		int minorVersion = 0;

		std::stringstream versionStream(versionStr);
		versionStream >> majorVersion;
		versionStream.ignore(1); // Ignore the dot
		versionStream >> minorVersion;

		// Combine major and minor version to get the desired format (e.g., 3.3 or 330)
		int combinedVersion = majorVersion * 100 + minorVersion * 10;

		return combinedVersion;
	}

	/*------------------------------------------------------------------------------------------------------------------------------------------*/
	Application::Application(const std::string& name, uint32_t width, uint32_t height, glm::vec4 backgroundColor){		
		if (s_Instance) { //if there already is another instance
			THROW_RUNTIME_ERROR("There already is an instance of Application");
		}

		s_Instance = this;
		m_Window = std::make_unique<Window>(WindowProps(name, width, height, backgroundColor));
		m_Window->init();
		m_LayerStack = std::make_unique<LayerStack>();

		m_glslVersion = std::string("#version ") + std::to_string(getGLSLVersionInt());

		LOG_CONSTRUCTOR("Application");
	}
	Application::~Application() {	
		LOG_DESTRUCTOR("Application");
	}

	void Application::finalCheck() {
		if (m_ImGuiLayer == nullptr) {
			THROW_RUNTIME_ERROR("An ImGuiLayer must be specified!");
		}
	}
	void Application::run() {
		finalCheck();

		LOG("Application has started running");

		float currentTime;
		float lastFrameTime = 0.0f;

		TimeStep timeStep;
		while (m_Window->running()) {
			currentTime = (float)glfwGetTime(); //gets time since glfw started
			timeStep.setTime(currentTime);

			m_Window->onUpdate();

			for (Layer* layer : *m_LayerStack.get())
				layer->onUpdate(timeStep);

			if (m_ImGuiLayer) {
				m_ImGuiLayer->begin();
				m_ImGuiLayer->onUpdate(timeStep);
				for (Layer* layer : *m_LayerStack.get())
					layer->onImguiUpdate(timeStep);
				m_ImGuiLayer->end();
			}

			glfwSwapBuffers(Application::getGLFWWindow());
		}
	}
	
	void Application::pushLayer(Layer* layer) {
		m_LayerStack->pushLayer(layer);
	}
	void Application::popLayer(Layer* layer) {
		m_LayerStack->popLayer(layer);
	}

	bool Application::getKey(uint16_t GLFW_KEY_, bool return_false_if_any_imgui_windowIsFocused) {
		bool isKeyDown = ImGui::GetIO().KeysDown[GLFW_KEY_];
		if (return_false_if_any_imgui_windowIsFocused) {
			if (imgui_windowIsFocused()) {
				return false;
			}
		}

		return isKeyDown;
	}
	glm::vec2 Application::getMouseDelta(bool return_false_if_any_imgui_windowIsFocused) {
		if (return_false_if_any_imgui_windowIsFocused) {
			if (imgui_windowIsFocused()) {
				return glm::vec2(0.0f, 0.0f);
			}
		}

		ImVec2 mouseDelta = ImGui::GetIO().MouseDelta;
		return glm::vec2(mouseDelta.x, mouseDelta.y);
	}

	Application* Application::s_Instance = nullptr;
}