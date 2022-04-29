#pragma once
#include "time.h"

namespace golden { namespace usage {

	Timer Time::m_Maintimer;
	float Time::m_LastFrameTime = 0.0f;
	Timestep Time::m_Timestep = 0.0f;

	void Time::init()
	{
		m_Maintimer.start();
	}

	void Time::update()
	{
		float bufferTime = m_Maintimer.elapsedSeconds();

		m_Timestep = bufferTime - m_LastFrameTime; // calculate timestep
		m_LastFrameTime = bufferTime; // update last frame time
	}

	float Time::getTime()	    { return m_Maintimer.elapsedSeconds();      }
	float Time::getTimestep()   { return m_Timestep.getSeconds();           }
	float Time::getTimeMs()     { return m_Maintimer.elapsedMilliseconds(); }
	float Time::getTimestepMs() { return m_Timestep.getMiliseconds();		}
}}