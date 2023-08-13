#pragma once
#include "Core.hpp"
#include "Layer.hpp"

namespace GLCore {
	class LayerStack {
	private:
		std::vector<Layer*> m_Layers;
	public:
		LayerStack();
		~LayerStack();

		void pushLayer(Layer* layer);
		void popLayer(Layer* layer);

		std::vector<Layer*>::iterator begin() { return m_Layers.begin(); }
		std::vector<Layer*>::iterator end() { return m_Layers.end(); }
	};
}