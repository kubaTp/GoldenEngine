#pragma once

#if defined(_WIN32) || defined(WIN32)
	#include <Windows.h>
#endif

namespace golden {

	class ProjectUtils
	{
	public:
		ProjectUtils() { }

	public:
		void showWindow(bool show = true)
		{
			m_Console = GetConsoleWindow();
			ShowWindow(m_Console, show);
		}

	private:
		HWND m_Console;
	};
}