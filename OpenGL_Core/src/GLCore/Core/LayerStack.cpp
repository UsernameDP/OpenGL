#include "pch.hpp"
#include "LayerStack.hpp"

namespace GLCore {
	LayerStack::LayerStack() {}
	LayerStack::~LayerStack() {}

	void LayerStack::pushLayer(Layer* layer) {
		std::shared_ptr<Layer> newLayer(layer);

		layers.push_back(newLayer);
		newLayer->onAttach();
	}
	void LayerStack::pushLayer(std::shared_ptr<Layer> layer) {
		layers.push_back(layer);
		layer.get()->onAttach();
	}
}