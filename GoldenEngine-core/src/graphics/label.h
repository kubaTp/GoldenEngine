#pragma once

#include "renderable2D.h"
#include "fontmanager.h" // includes font.h

namespace golden { 	
	namespace graphics {

		class Label : public Renderable2D
		{
		public:
			std::string content;
			maths::Vec3 position;
			Font* m_Font;

		public:
			Label(float x, float y, const uint32_t color);
			Label(const std::string& content, float x, float y, const uint32_t color);
			Label(const std::string& content, float x, float y, Font* font, const uint32_t color);
			Label(const std::string& content, float x, float y, FontType fontType, const uint32_t color);
			Label(const std::string& content, float x, float y, FontType fontType, const uint16_t size, const uint32_t color);

			void submit(Renderer2D* renderer) const override;
		};
	}
}