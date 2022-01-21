#pragma once

#include "component.h"
#include "../maths/maths.h"

namespace golden { namespace ecs {

	class TransformComponent : public Component
	{
	public:
		TransformComponent() { compType = ComponentsType::TRANSFORM_COMPONENT; setVecsDefault(); }

	public:
		void Translate(const maths::Vec3 pos) // constant movement in direction
		{

		}

		void Rotate(const maths::Vec3 rot) // consant rotation in given vec3
		{

		}

	private:
		maths::Vec3& sum() const { return position * rotation * scale; }

		void setVecsDefault() 
		{
			position = maths::Vec3(1, 1, 1);
			scale    = maths::Vec3(1, 1, 1);
			rotation = maths::Vec3(1, 1, 1);
		}

	public:
		maths::Vec3 position; // position given
		maths::Vec3 scale;	  // scale given
		maths::Vec3 rotation; // rotation given
	};
}}