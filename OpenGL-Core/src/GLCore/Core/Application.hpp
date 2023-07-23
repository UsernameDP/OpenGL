#pragma once
#include "Core.hpp"
#include <glm/vec4.hpp>
#include "Layer.hpp"
#include "LayerStack.hpp"
#include "Window.hpp"

namespace GLCore {

	class Application {
	private:
		static Application* s_Instance;
		static std::unique_ptr<Window> m_Window;
		static const std::string& glslVersion;
	private:
		LayerStack layerStack;
		bool running;

	public:
		Application(const std::string& name = "GLFW Window",
			uint32_t width = 1280, 
			uint32_t height = 720, 
			glm::vec4 backgroundColor =  glm::vec4(0.0, 0.0, 0.0, 1.0));
		virtual ~Application() = default;

		virtual void init(); //other things to do before run() 
		void run();

		void pushLayer(Layer* layer);
		void popLayer(Layer* layer);
		void setImGuiLayer();

		static Application& get();
		inline static GLFWwindow* getGLFWWindow() { return m_Window.get()->getGLFWWindow(); }
	};
};