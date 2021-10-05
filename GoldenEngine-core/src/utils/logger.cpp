#include "logger.h"

#if 1
HANDLE golden::Logger::m_Handle = GetStdHandle(STD_OUTPUT_HANDLE);

namespace golden {

	void Logger::log(uint8_t colorindex, std::string& text)
	{
		SetConsoleTextAttribute(m_Handle, colorindex);
		std::cout << text << std::endl;
		SetConsoleTextAttribute(m_Handle, 7);
	}

	void Logger::logGoldenEngine()
	{
#ifdef _WIN32
		system("CLS");
#else
		system("CLEAR");
#endif
		SetConsoleTextAttribute(m_Handle, 2);
		std::cout << "Golden Engine 1.0.01\n" << "  - irrKlang sound library version 1.6.0" << "\n  - OpenGL: " << glGetString(GL_VERSION) << "\n\n" << std::endl;
		SetConsoleTextAttribute(m_Handle, 7);
	}
}
#endif