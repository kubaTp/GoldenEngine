#pragma once

#include "../utils/timestep.h"
#include "../utils/timer.h"

namespace golden { namespace usage {

	class Time
	{
	private:
		Time() { }

	public:
		static void init(); // start measuring the time
		static void update(); // set new time and update variables

		static float getTime();
		static float getTimestep();
		static float getTimeMs();
		static float getTimestepMs();

		friend class Input;

	private:
		static Timer m_Maintimer;
		static float m_LastFrameTime;
		static Timestep m_Timestep;
	};

	class Input;
}}