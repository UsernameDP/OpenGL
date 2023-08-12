#include "pch.hpp"
#include "Layer.hpp"

namespace GLCore {
	Layer::Layer(const std::string& name) : m_DebugName(name) {
		LOG_CONSTRUCTOR(name + "<Layer>");
	}
	Layer::~Layer() {
		LOG_DESTRUCTOR("Layer<name=" + m_DebugName + ">");
	}
}