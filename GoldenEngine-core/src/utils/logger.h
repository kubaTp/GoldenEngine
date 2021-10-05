#pragma once

/*NOTE: Logger is a static class which is responsible for all information loggin in the console window*/
/*NOTE: logger.h needs to attached on the very top of file*/
#ifdef _WIN32
	#include "Windows.h"
#endif

#include <string>
#include <iostream>
#include <GL/glew.h>

namespace golden {

	namespace graphics { class Window; }

	class Logger
	{
	private:
		Logger() { }

	public:
		static void logInfo(std::string text) { log(7, text); } // log internal info
		static void logWarning(std::string text) { log(6, text); } // log internal warning
		static void logError(std::string text) { log(4, text); } // log internal error
		static void logSpace() { std::cout << '\n'; } // logs empty space

	private:
		friend class graphics::Window;
		static void logGoldenEngine(); // log golden engine infos // friendly void for chief

	private:
		static void log(uint8_t colorindex, std::string& text);

	private:
		static HANDLE m_Handle;
	};
}