#include "sprite.h"

namespace golden { namespace graphics {

	// constructors without name
	Sprite::Sprite(float x, float y, float width, float heigh, const uint32_t color) 
		: Renderable2D(maths::Vec3(x, y, 0), maths::Vec2(width, heigh), color) 
	{
		getComponent<ecs::TransformComponent>()->position = maths::Vec3(x, y, 0);
	}

	Sprite::Sprite(float x, float y, float width, float heigh, Texture* texture) 
		: Renderable2D(maths::Vec3(x, y, 0), maths::Vec2(width, heigh), 0xffffffff)
	{ 
		m_Texture = texture;
		getComponent<ecs::TransformComponent>()->position = maths::Vec3(x, y, 0);
	}

	Sprite::Sprite(float x, float y, float width, float heigh, const maths::Vec4 color) 
		: Renderable2D(maths::Vec3(x, y, 0), maths::Vec2(width, heigh), color) 
	{
		getComponent<ecs::TransformComponent>()->position = maths::Vec3(x, y, 0);
	}

	// constructors with name
	Sprite::Sprite(std::string name, float x, float y, float width, float heigh, const uint32_t color)
		: Renderable2D(name, maths::Vec3(x, y, 0), maths::Vec2(width, heigh), color)
	{
		getComponent<ecs::TransformComponent>()->position = maths::Vec3(x, y, 0);
	}

	Sprite::Sprite(std::string name, float x, float y, float width, float heigh, Texture* texture)
		: Renderable2D(name, maths::Vec3(x, y, 0), maths::Vec2(width, heigh), 0xffffffff)
	{
		m_Texture = texture;
		getComponent<ecs::TransformComponent>()->position = maths::Vec3(x, y, 0);
	}

	Sprite::Sprite(std::string name, float x, float y, float width, float heigh, const maths::Vec4 color)
		: Renderable2D(name, maths::Vec3(x, y, 0), maths::Vec2(width, heigh), color)
	{
		getComponent<ecs::TransformComponent>()->position = maths::Vec3(x, y, 0);
	}
}}