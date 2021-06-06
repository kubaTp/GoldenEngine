#include "sprite.h"

namespace golden { namespace graphics {

	Sprite::Sprite(float x, float y, float width, float heigh, const uint32_t color) : Renderable2D(maths::Vec3(x, y, 0), maths::Vec2(width, heigh), color) { }
	Sprite::Sprite(float x, float y, float width, float heigh, Texture* texture) : Renderable2D(maths::Vec3(x, y, 0), maths::Vec2(width, heigh), 0xffffffff) 
	{ 
		m_Texture = texture; 
	}

	Sprite::Sprite(float x, float y, float width, float heigh, const maths::Vec4 color) : Renderable2D(maths::Vec3(x, y, 0), maths::Vec2(width, heigh), color) { }
}}