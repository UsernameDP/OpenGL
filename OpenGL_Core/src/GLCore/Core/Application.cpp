#include "pch.hpp"
#include "Window.hpp"
#include "Application.hpp"

namespace GLCore
{

	Application *instance = nullptr;

	WindowLayer::WindowLayer(std::shared_ptr<Window> window, std::shared_ptr<LayerStack> layers)
	{
		this->window = window;
		this->layers = layers;
	}

	Application::Application()
	{
		if (instance == nullptr)
		{
			Application::instance = this;
		}
		else
		{
			LOG_ERROR("Application instance already exists");
		}
	}
	Application::~Application() {}

	void Application::pushWindowLayer(
		std::shared_ptr<Window> window,
		std::shared_ptr<LayerStack> layers)
	{

		if (windowLayers.at(window->getName()).get() != nullptr)
		{
			LOG_ERROR("Window with name {0} already exists", window->getName());
		}
		else
		{
			windowLayers[window->getName()] = std::make_shared<WindowLayer>(
				window, layers);
		}
	}

	bool Application::running()
	{
		for (const auto &windowLayer : windowLayers)
		{
			if (windowLayer.second.get()->window.get()->running())
			{
				return true;
			}
		}
		return false;
	}

	void Application::run()
	{

		float currentTime;

		TimeStep timeStep;

		while (running())
		{
			currentTime = (float)glfwGetTime();
			timeStep.setTime(currentTime);

			for (const auto &windowLayer : windowLayers)
			{
				Window *window = windowLayer.second->window.get();
				LayerStack *layers = windowLayer.second->layers.get();

				for (const std::shared_ptr<Layer> layer : *layers)
				{
					layer->onUpdate(timeStep);
				}

				glfwSwapBuffers(window->getGLFWWindow());
			}
		}
	}

}