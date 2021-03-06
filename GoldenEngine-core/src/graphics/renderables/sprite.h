#pragma once

#include "renderable2D.h"

namespace golden { namespace graphics {

	class Sprite : public Renderable2D
	{
	public:
		Sprite() {}
		Sprite(float x, float y, float width, float heigh, const uint32_t color);
		Sprite(float x, float y, float width, float heigh, const maths::Vec4 color);
		Sprite(float x, float y, float width, float heigh, Texture* texture);


		Sprite(std::string name, float x, float y, float width, float heigh, const uint32_t color);
		Sprite(std::string name, float x, float y, float width, float heigh, const maths::Vec4 color);
		Sprite(std::string name, float x, float y, float width, float heigh, Texture* texture);
		//~Sprite();
	};
}}