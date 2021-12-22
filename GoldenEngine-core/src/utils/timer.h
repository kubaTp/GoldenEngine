#pragma once

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