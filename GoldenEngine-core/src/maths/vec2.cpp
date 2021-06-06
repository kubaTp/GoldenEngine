#include "vec2.h"

namespace golden { namespace maths {

	Vec2::Vec2()
	{
		x = 0.0f;
		y = 0.0f;
	}

	Vec2::Vec2(const float& x, const float& y)
	{
		this->x = x;
		this->y = y;
	}

	Vec2& Vec2::add(const Vec2& other)
	{
		x += other.x;
		y += other.y;

		return *this;
	}

	Vec2& Vec2::subtrack(const Vec2& other)
	{
		x -= other.x;
		y -= other.y;

		return *this;
	}

	Vec2& Vec2::multiply(const Vec2& other)
	{
		x *= other.x;
		y *= other.y;

		return *this;
	}

	Vec2& Vec2::devide(const Vec2& other)
	{
		x /= other.x;
		y /= other.y;

		return *this;
	}

	Vec2& operator+(Vec2 left, const Vec2& right)
	{
		return left.add(right);
	}

	Vec2& operator-(Vec2 left, const Vec2& right)
	{
		return left.subtrack(right);
	}

	Vec2& operator*(Vec2 left, const Vec2& right)
	{
		return left.multiply(right);
	}

	Vec2& operator/(Vec2 left, const Vec2& right)
	{
		return left.devide(right);
	}


	Vec2& Vec2::operator+=(const Vec2& other)
	{
		return add(other);
	}

	Vec2& Vec2::operator-=(const Vec2& other)
	{
		return subtrack(other);
	}

	Vec2& Vec2::operator*=(const Vec2& other)
	{
		return multiply(other);
	}

	Vec2& Vec2::operator/=(const Vec2& other)
	{
		return devide(other);
	}

	bool Vec2::operator==(const Vec2& other)
	{
		return x == other.x && y == other.y;
	}
	bool Vec2::operator!=(const Vec2& other)
	{
		return x != other.x && y != other.y;
	}

	std::ostream& operator<<(std::ostream& stream, const Vec2& vector)
	{
		stream << "vec2: (" << vector.x << ", " << vector.y << ")";
		return stream;
	}
}}