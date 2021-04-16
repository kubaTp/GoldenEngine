#pragma once

#include <iostream>

namespace golden
{
	namespace maths
	{
		struct Vec4
		{
			float x, y, z, w;

			Vec4() = default;
			Vec4(const float& x, const float& y, const float& z, const float& w);

			Vec4& add(const Vec4& other);
			Vec4& subtrack(const Vec4& other);
			Vec4& multiply(const Vec4& other);
			Vec4& devide(const Vec4& other);

			friend Vec4& operator+(Vec4 left, const Vec4& right);
			friend Vec4& operator-(Vec4 left, const Vec4& right);
			friend Vec4& operator*(Vec4 left, const Vec4& right);
			friend Vec4& operator/(Vec4 left, const Vec4& right);

			bool operator==(const Vec4& other);
			bool operator!=(const Vec4& other);

			Vec4& operator+=(const Vec4& other);
			Vec4& operator-=(const Vec4& other);
			Vec4& operator*=(const Vec4& other);
			Vec4& operator/=(const Vec4& other);

			friend std::ostream& operator<<(std::ostream& stream, const Vec4& vector);
		};
	}
}