#pragma once
#include "TimeStep.hpp"

namespace GLCore {
	class Layer {
	protected:
		std::string name;
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer() = 0;

		virtual void onAttach() = 0;
		virtual void onDetach() = 0;
		virtual void onUpdate(const TimeStep& ts) = 0;
		virtual void onImguiUpdate(const TimeStep& ts) = 0;

		inline const std::string& getName() const { return name; }
	};
}