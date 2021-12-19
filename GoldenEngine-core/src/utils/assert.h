#pragma once
/*NOTE : utility file which defines assert*/

#include <string>
#include <sstream>
#include "logger.h"

// TODO : add asserting shaders

namespace golden {

	#define GE_ASSERT(x, s) if(x == true) { Logger::logError(s); exit(0); }
	#define GE_ASSERT_WARNING(x, s) if(x == true) {Logger::logWarning(s); }

	#define GE_ASSERT_OPENGL(x, s1, s2) if(x == true) {std::stringstream ss; ss << s1 << s2; Logger::logError(ss.str()); exit(0); }
	#define GE_ASSERT_OPENGL_WARNING(x, s1, s2) if(x == true) {std::stringstream ss; ss << s1 << s2; Logger::logWarning(ss.str()); }
}