#include "label.h"

namespace golden {  namespace graphics {

	Label::Label(float x, float y, const uint32_t color)
		: Renderable2D(), content("Golden Engine text"), m_Font(FontManager::get(FontType::Inter_Regular))
	{
		getComponent<ecs::TransformComponent>()->position = maths::Vec3(x, y, 0.0f);
		m_Color = color;
	}

	Label::Label(const std::string& content, float x, float y, const uint32_t color)
		: Renderable2D(), content(content), m_Font(FontManager::get(FontType::Inter_Regular))
	{
		getComponent<ecs::TransformComponent>()->position = maths::Vec3(x, y, 0.0f);
		m_Color = color;
	}

	Label::Label(const std::string& content, float x, float y, Font* font, const uint32_t color)
		: Renderable2D(), content(content), m_Font(font)
	{
		getComponent<ecs::TransformComponent>()->position = maths::Vec3(x, y, 0.0f);
		m_Color = color;
	}

	Label::Label(const std::string& content, float x, float y, FontType fontType, const uint32_t color)
		: Renderable2D(), content(content), m_Font(FontManager::get(fontType))
	{
		getComponent<ecs::TransformComponent>()->position = maths::Vec3(x, y, 0.0f);
		m_Color = color;
	}

	Label::Label(const std::string& content, float x, float y, FontType fontType, const uint16_t size, const uint32_t color)
		: Renderable2D(), content(content), m_Font(FontManager::get(fontType, size))
	{
		getComponent<ecs::TransformComponent>()->position = maths::Vec3(x, y, 0.0f);
		m_Color = color;
	}

	void Label::submit(Renderer2D* renderer) const
	{
		renderer->drawString(content, getComponent<ecs::TransformComponent>()->position, *m_Font, m_Color);
	}
}}
