#include "renderable2D.h"

namespace golden { namespace graphics {

	Renderable2D::Renderable2D() : m_Texture(nullptr)
	{
		setDefaultOfUV();
		m_Components.push_back(new ecs::BehaviourComponent());
	}

	Renderable2D::Renderable2D(maths::Vec3 position, maths::Vec2 size, uint32_t color)
		: m_Position(position), m_Size(size), m_Color(color), m_Texture(nullptr)
	{
		setDefaultOfUV();
		m_Components.push_back(new ecs::BehaviourComponent());
	}

	Renderable2D::Renderable2D(maths::Vec3 position, maths::Vec2 size, const maths::Vec4& color)
		: m_Position(position), m_Size(size), m_Color(convertColor(color))
	{
		setDefaultOfUV();
		m_Components.push_back(new ecs::BehaviourComponent());
	}

	Renderable2D::~Renderable2D() { }

	void Renderable2D::submit(Renderer2D* renderer) const 
	{
		renderer->submit(this);
	}

	uint32_t Renderable2D::convertColor(const maths::Vec4& vec)
	{
		// color is from 0 to 1 in float
		uint8_t r = vec.x * 255.0f;
		uint8_t g = vec.y * 255.0f;
		uint8_t b = vec.z * 255.0f;
		uint8_t a = vec.w * 255.0f;

		uint32_t color = a << 24 | b << 16 | g << 8 | r; // push alfa to the first byte, push b to second byte, push g to third byte, push r to fourth 
		return color;
	}

	ecs::Component* Renderable2D::getComponent(std::string name) const
	{
		if (m_Components.size() > 0)
		{
			for (ecs::Component* comp : m_Components)
			{
				if (comp->getName() == name)
				{
					return comp;
				}
			}
		}
		else
		{
			return new ecs::Component;
		}
	}
}}