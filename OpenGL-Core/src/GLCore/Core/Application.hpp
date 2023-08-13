#pragma once
#include "Core.hpp"
#include "Window.hpp"
#include "LayerStack.hpp"
#include "GLCore/ImGui/ImGuiLayer.hpp"
#include "GLCore/Extension/util/AssetPoolINIT.hpp"
#include <glm/glm.hpp>

namespace GLCore {

	class Application {
	private:
		static Application* s_Instance; //std::unique_ptr always b/c Runner.hpp
	private:
		std::unique_ptr<Window> m_Window = nullptr;
		std::unique_ptr<ImGuiLayer> m_ImGuiLayer = nullptr;
		std::unique_ptr<LayerStack> m_LayerStack = nullptr;
		std::unique_ptr<util::AssetPoolINIT> m_AssetPoolINIT = nullptr;
		std::string m_glslVersion = "";
		bool m_running;
	public:
		Application(const std::string& name,
			uint32_t width,
			uint32_t height,
			glm::vec4 backgroundColor);
		virtual ~Application();

		virtual void init() = 0; //other things to do before run() 
		void finalCheck();
		void run();

		void pushLayer(Layer* layer);
		void popLayer(Layer* layer);

		inline void setImGuiLayer(std::unique_ptr<ImGuiLayer> layer) {m_ImGuiLayer = std::move(layer); m_ImGuiLayer->onAttach();}
		inline void initializeAssetPool(std::unique_ptr<util::AssetPoolINIT> settings) { m_AssetPoolINIT = std::move(settings); m_AssetPoolINIT->configure(); }

	public:
		static inline bool imgui_windowIsFocused() {
			return ImGui::IsWindowFocused(ImGuiFocusedFlags_AnyWindow);
		}
		static inline bool imgui_rightClickOnHold() {
			return ImGui::IsMouseDown(ImGuiMouseButton_Right);
		}
		static bool getKey(uint16_t GLFW_KEY, bool return_false_if_any_imgui_windowIsFocused = false);
		static glm::vec2 getMouseDelta(bool return_nothing_if_any_imgui_windowIsFocused = false, bool return_nothing_if_rightIsHeld = false);
		
		static inline Application* get() { return s_Instance; }
		static inline Window* getWindow() { return get()->m_Window.get(); };
		static inline GLFWwindow* getGLFWWindow() { return getWindow()->getGLFWWindow(); }
		static inline const std::string& getGLSLVersion() { return get()->m_glslVersion; }
	};
};
