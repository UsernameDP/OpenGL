#include "pch.hpp"
#include "Application.hpp"

namespace GLCore
{

	Application* Application::instance = nullptr;

	Application::Application(const std::string& name,
		uint32_t width,
		uint32_t height,
		const glm::vec4& backgroundColor)
	{
		if (instance == nullptr)
		{
			GLCore::Log::init();
			Application::instance = this;
		}
		else
		{
			LOG_ERROR("Application instance already exists");
		}

		WindowProps props = WindowProps(name, width, height, backgroundColor);
		this->window = std::make_unique<Window>(props);

		imguiLayer = new ImGuiLayer();
		pushLayerFront(imguiLayer);
	}

	void Application::run()
	{
		if (window.get() == nullptr) {
			LOG_ERROR("Application's window is not set!!");
		}

		float currentTime;

		TimeStep timeStep;

		while ( window->running() )
		{
			currentTime = (float)glfwGetTime();
			timeStep.setTime(currentTime);

			for (Layer* layer : *layers) {
				layer->onUpdate(timeStep);
			}

			imguiLayer->begin();
			for (Layer* layer : *layers) {
				layer->onImguiUpdate(timeStep);
			}
			imguiLayer->end();

			glfwSwapBuffers(window->getGLFWWindow());
		}
	}

}