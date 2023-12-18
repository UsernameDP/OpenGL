#pragma once
#include "Window.hpp"
#include "LayerStack.hpp"

namespace GLCore
{

	struct WindowLayer
	{
		std::shared_ptr<Window> window;
		std::shared_ptr<LayerStack> layers;

		WindowLayer(std::shared_ptr<Window> window, std::shared_ptr<LayerStack> layers);
	};

	class Application
	{
	private:
		static Application *instance;

	private:
		std::unordered_map<std::string, std::shared_ptr<WindowLayer>> windowLayers;

	public:
		Application();
		virtual ~Application();
		virtual void init() = 0;
		virtual void run();

		void pushWindowLayer(std::shared_ptr<Window> window, std::shared_ptr<LayerStack> layers);

		bool running();
		inline std::shared_ptr<WindowLayer> getWindowLayer(const std::string &name) { return this->windowLayers.at(name); }

	public:
		static inline Application *get() { return Application::instance; }
	};

}