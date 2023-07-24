#pragma once
#include "Core.hpp"
#include <glm/vec4.hpp>
#include "Layer.hpp"
#include "LayerStack.hpp"
#include "Window.hpp"
#include "GLCore/ImGui/ImGuiLayer.hpp"

namespace GLCore {

	class Application {
	private:
		static Application* s_Instance;
	private:
		Window* m_Window = nullptr;
		ImGuiLayer* m_ImGuiLayer = nullptr;
		const std::string& m_glslVersion = "";
		LayerStack m_LayerStack;
		bool m_running;
	public:
		Application(const std::string& name,
			uint32_t width,
			uint32_t height,
			glm::vec4 backgroundColor);
		~Application();
		void destroy();
		void manualDestroy(); //run this to delete Application if Application is not created with std::unique_ptr
		virtual void extraDestroy(); //extra things to detach beyond layerStack, Window, and ImGui

		virtual void init(); //other things to do before run() 
		void run();

		void pushLayer(Layer* layer);
		void popLayer(Layer* layer);
		void setImGuiLayer(ImGuiLayer* imGuiLayer);

	public:
		static bool getKey(uint16_t GLFW_KEY, bool return_false_if_any_imgui_windowIsFocused = false);
		inline static Application*& get() { return s_Instance; }
		inline static Window*& getWindow() { return get()->m_Window; };
		inline static GLFWwindow*& getGLFWWindow() { return getWindow()->getGLFWWindow(); }
	};
};
