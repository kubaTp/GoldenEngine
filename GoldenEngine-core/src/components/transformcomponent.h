#pragma once

#include "component.h"


// TODO : right now scale works as width and height of renderable
// it needs to be fixed in the future
namespace golden { namespace ecs {

	class TransformComponent : public Component
	{
	public:
		TransformComponent() { compType = ComponentsType::TRANSFORM_COMPONENT; setVecsDefault(); }

	private:
		maths::Vec3& sum() const { return position * rotation * scale; }

		void setVecsDefault() 
		{
			position = maths::Vec3(1, 1, 1);
			scale    = maths::Vec3(1, 1, 1);
			rotation = maths::Vec3(0, 0, 0);
		}

	public:
		maths::Vec3 position; // position given
		maths::Vec3 scale;	  // scale given
		maths::Vec3 rotation; // rotation given
	};
}}