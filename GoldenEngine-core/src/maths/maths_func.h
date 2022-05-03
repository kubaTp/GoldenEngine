#pragma once

#define _USE_MATH_DEFINES
#include <math.h>
#include <sstream>
#include <iomanip>

namespace golden { namespace maths {

	inline float toRadians(float degress)
	{
		return degress * (M_PI / 180.0f);
	}

    inline float precisionRoundedFloat(float val)
    {
        std::stringstream ss;
        ss << std::fixed << std::setprecision(1) << val;

        float result = std::stof(ss.str());

        return round(result);
    }
}}