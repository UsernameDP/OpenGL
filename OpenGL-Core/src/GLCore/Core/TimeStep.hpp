#pragma once

namespace GLCore {
	class TimeStep {
	private:
		float m_Time;
	public:
		TimeStep() = default;
		TimeStep(float time) :m_Time(time) {}

		operator float() const { return m_Time; }

		void setTime(float time) { this->m_Time = time; }
		float getSeconds() const { return m_Time; }
		float getMilliseconds() const { return m_Time * 1000.0f; }
	};
}