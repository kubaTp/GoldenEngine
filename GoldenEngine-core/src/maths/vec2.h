#pragma once

#include <iostream>

namespace golden
{
	namespace maths
	{
		struct Vec2
		{
			float x, y;

			Vec2();
			Vec2(const float& x, const float& y);

			Vec2& add(const Vec2& other);
			Vec2& subtrack(const Vec2& other);
			Vec2& multiply(const Vec2& other);
			Vec2& devide(const Vec2& other);

			friend Vec2& operator+(Vec2 left, const Vec2& right);
			friend Vec2& operator-(Vec2 left, const Vec2& right);
			friend Vec2& operator*(Vec2 left, const Vec2& right);
			friend Vec2& operator/(Vec2 left, const Vec2& right);

			bool operator==(const Vec2& other);
			bool operator!=(const Vec2& other);

			Vec2& operator+=(const Vec2& other);
			Vec2& operator-=(const Vec2& other);
			Vec2& operator*=(const Vec2& other);
			Vec2& operator/=(const Vec2& other);

			friend std::ostream& operator<<(std::ostream& stream, const Vec2& vector);
		};
	}
}