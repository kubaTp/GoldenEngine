#pragma once

#define _USE_MATH_DEFINES
#include <math.h>

namespace golden
{
	namespace maths
	{
		inline float toRadians(float degress)
		{
			return degress * (M_PI / 180.0f);
		}
	}
}