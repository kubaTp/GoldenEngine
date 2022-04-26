#pragma once

#include <string>
#include "../maths/maths.h"

namespace golden { namespace graphics {

	class Camera
	{
	public:
		std::string name;
		maths::Vec3 position;
		maths::Vec3 rotation;

	public:
		Camera();
		Camera(std::string name, maths::Vec3 pos, maths::Vec3 rot);

		const maths::Mat4  cameraMatrix() const;	
	};
}}