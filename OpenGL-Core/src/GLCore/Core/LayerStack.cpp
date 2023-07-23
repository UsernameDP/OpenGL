#include "glpch.hpp"
#include "LayerStack.hpp"

namespace GLCore {
	LayerStack::LayerStack() {}
	LayerStack::~LayerStack() {
		for (Layer* layer : m_Layers) {
			delete layer;
		}
	}

	void LayerStack::pushLayer(Layer* layer) {
		m_Layers.push_back(layer);
		layer->onAttach();
	}
	void LayerStack::popLayer(Layer* layer) {
		auto it = std::find(m_Layers.begin(), m_Layers.end(), layer);
		if (it != m_Layers.end()) {
			layer->onDetach();
			m_Layers.erase(it);
		}
		else {
			THROW_RUNTIME_ERROR(layer->getName() + " not found");
		}
	}
}