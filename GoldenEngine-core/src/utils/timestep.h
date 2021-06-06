#pragma once

// construct deltatime, timestep for sync moving

namespace golden {

	class Timestep
	{
	public:
		Timestep(float time) : m_Time(time) {}

		float getSeconds() const { return m_Time; }
		float getMiliseconds() const { return  m_Time * 1000.0f; }

	private:
		float m_Time = 0.0f;
	};
}