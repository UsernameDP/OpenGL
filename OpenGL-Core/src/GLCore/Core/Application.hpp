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
		static Application* s_Instance; //std::unique_ptr always b/c Runner.hpp
	private:
		std::unique_ptr<Window> m_Window = nullptr;
		std::unique_ptr<ImGuiLayer> m_ImGuiLayer = nullptr;
		std::unique_ptr<LayerStack> m_LayerStack = nullptr;
		std::string m_glslVersion = "";
		bool m_running;
	public:
		Application(const std::string& name,
			uint32_t width,
			uint32_t height,
			glm::vec4 backgroundColor);
		~Application();
		virtual void extraDestructor(); //extra things to detach beyond layerStack, Window, and ImGui

		virtual void init(); //other things to do before run() 
		void run();

		void pushLayer(Layer* layer);
		void popLayer(Layer* layer);
		void setImGuiLayer(std::unique_ptr<ImGuiLayer> layer);

	public:
		static bool getKey(uint16_t GLFW_KEY, bool return_false_if_any_imgui_windowIsFocused = false);
		inline static Application* get() { return s_Instance; }
		inline static Window* getWindow() { return get()->m_Window.get(); };
		inline static GLFWwindow* getGLFWWindow() { return getWindow()->getGLFWWindow(); }
		inline static std::string& getGLSLVersion() { return get()->m_glslVersion; }
	};
};
