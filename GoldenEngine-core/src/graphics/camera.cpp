#include "camera.h"

namespace golden { namespace graphics {

	Camera::Camera() : name("unnamed") { }

	Camera::Camera(std::string name, maths::Vec3 pos, maths::Vec3 rot) 
		: name(name), position(pos), rotation(rot) { }

	const maths::Mat4 Camera::cameraMatrix() const
	{
		maths::Mat4 finalmatrix = maths::Mat4::idenity();

		// rotation
		if (rotation.x > 0)
			finalmatrix *= maths::Mat4::rotation(rotation.x, maths::Vec3(1, 0, 0));

		if (rotation.y > 0)
			finalmatrix *= maths::Mat4::rotation(rotation.y, maths::Vec3(0, 1, 0));

		if (rotation.z > 0)
			finalmatrix *= maths::Mat4::rotation(rotation.z, maths::Vec3(0, 0, 1));

		// translation
		finalmatrix *= maths::Mat4::translation(position);

		return finalmatrix;
	}
}}