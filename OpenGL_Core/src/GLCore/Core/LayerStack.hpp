#pragma once
#include "Layer.hpp"

namespace GLCore {
	class LayerStack {
	private:
		std::vector<std::shared_ptr<Layer>> layers;
	public:
		LayerStack();
		~LayerStack();

		void pushLayer(Layer* layer);
		void pushLayer(std::shared_ptr<Layer> layer);
		//void popLayer(const std::string& name); Remove is not needed most likely

		std::vector<std::shared_ptr<Layer>>::iterator begin() { return layers.begin(); }
		std::vector<std::shared_ptr<Layer>>::iterator end() { return layers.end(); }
	};
}