#pragma once

namespace GLCore {
	class TimeStep {
	private:
		float m_Time;
	public:
		TimeStep() = default;
		inline TimeStep(float time) :m_Time(time) {}

		inline operator float() const { return m_Time; }

		inline void setTime(float time) { this->m_Time = time; }
		inline float getSeconds() const { return m_Time; }
		inline float getMilliseconds() const { return m_Time * 1000.0f; }
	};
}