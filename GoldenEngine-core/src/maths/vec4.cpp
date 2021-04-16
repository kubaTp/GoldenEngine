#include "vec4.h"

namespace golden
{
	namespace maths
	{
		Vec4::Vec4(const float& x, const float& y, const float& z, const float& w)
		{
			this->x = x;
			this->y = y;
			this->z = z;
			this->w = w;
		}

		Vec4& Vec4::add(const Vec4& other)
		{
			x += other.x;
			y += other.y;
			z += other.z;
			w += other.w;

			return *this;
		}

		Vec4& Vec4::subtrack(const Vec4& other)
		{
			x -= other.x;
			y -= other.y;
			z -= other.z;
			w -= other.w;

			return *this;
		}

		Vec4& Vec4::multiply(const Vec4& other)
		{
			x *= other.x;
			y *= other.y;
			z *= other.z;
			w *= other.w;

			return *this;
		}

		Vec4& Vec4::devide(const Vec4& other)
		{
			x /= other.x;
			y /= other.y;
			z /= other.z;
			w /= other.w;

			return *this;
		}

		Vec4& operator+(Vec4 left, const Vec4& right)
		{
			return left.add(right);
		}

		Vec4& operator-(Vec4 left, const Vec4& right)
		{
			return left.subtrack(right);
		}

		Vec4& operator*(Vec4 left, const Vec4& right)
		{
			return left.multiply(right);
		}

		Vec4& operator/(Vec4 left, const Vec4& right)
		{
			return left.devide(right);
		}

		Vec4& Vec4::operator+=(const Vec4& other)
		{
			return add(other);
		}

		Vec4& Vec4::operator-=(const Vec4& other)
		{
			return subtrack(other);
		}

		Vec4& Vec4::operator*=(const Vec4& other)
		{
			return multiply(other);
		}

		Vec4& Vec4::operator/=(const Vec4& other)
		{
			return devide(other);
		}

		bool Vec4::operator==(const Vec4& other)
		{
			return x == other.x && y == other.y && z == other.z && w == other.w;
		}
		bool Vec4::operator!=(const Vec4& other)
		{
			return x != other.x && y != other.y && z != other.z && w != other.w;
		}

		std::ostream& operator<<(std::ostream& stream, const Vec4& vector)
		{
			stream << "vec4: (" << vector.x << ", " << vector.y << ", " << vector.z << ", " << vector.w << ")";
			return stream;
 		}
	}
}