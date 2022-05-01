#pragma once

#if 0
#define NOMINMAX 1
#include "Windows.h"

namespace golden {

	static class Timer
	{
	public:
		static void reset() { QueryPerformanceCounter(&m_Start); }

		static float elapsed()
		{
			LARGE_INTEGER current;
			QueryPerformanceCounter(&current);
			unsigned __int64 cycles = current.QuadPart - m_Start.QuadPart;
			return (float)(cycles * m_Frequency);
		}

	private:
		static LARGE_INTEGER m_Start;
		static double m_Frequency;

		static void startTimer()
		{
			LARGE_INTEGER frequency;
			QueryPerformanceFrequency(&frequency);
			m_Frequency = 1.0 / frequency.QuadPart;
			QueryPerformanceCounter(&m_Start);
		}
	};
}

#else
/*--- main timer ---*/

#include <chrono>
#include <ctime>
#include <cmath>

class Timer
{
public:
    Timer() { }
    ~Timer()
    {
        this->stop();
    }

public:
    void start()
    {
        m_StartTime = std::chrono::system_clock::now();
        m_Running = true;
    }

    void stop()
    {
        m_EndTime = std::chrono::system_clock::now();
        m_Running = false;
    }

    float elapsedMilliseconds()
    {
        std::chrono::time_point<std::chrono::system_clock> endTime;

        if (m_Running)
            endTime = std::chrono::system_clock::now();
        else
            endTime = m_EndTime;

        return std::chrono::duration_cast<std::chrono::milliseconds>(endTime - m_StartTime).count();
    }

    float elapsedSeconds() { return elapsedMilliseconds() / 1000.0; }

private:
    std::chrono::time_point<std::chrono::system_clock> m_StartTime;
    std::chrono::time_point<std::chrono::system_clock> m_EndTime;
    bool m_Running = false;
};

#endif
