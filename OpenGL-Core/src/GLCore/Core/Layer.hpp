#pragma once
#include "Core.hpp"
#include "TimeStep.hpp"

namespace GLCore {
	class Layer {
	protected:
		std::string m_DebugName;
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer() = default;

		virtual void onAttach() {}
		virtual void onDetach() {}
		virtual void onUpdate(const TimeStep& ts);
		virtual void onImguiUpdate(const TimeStep& ts);

		inline const std::string& getName() const { return m_DebugName; }
	};
}