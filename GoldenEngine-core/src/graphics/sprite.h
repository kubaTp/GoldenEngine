#pragma once

#include "renderable2D.h"

namespace golden { namespace graphics {

	class Sprite : public Renderable2D
	{
	private:
	public:
		Sprite(float x, float y, float width, float heigh, const maths::Vec4& color);
		//~Sprite();
	};
}}