#include "sprite.h"

namespace golden { namespace graphics {

	Sprite::Sprite(float x, float y, float width, float heigh, const maths::Vec4& color) : Renderable2D(maths::Vec3(x, y, 0), maths::Vec2(width, heigh), color) {}
}}