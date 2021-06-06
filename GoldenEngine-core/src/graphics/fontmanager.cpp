#include "fontmanager.h"


namespace golden {
	namespace graphics {

		std::vector<Font*> FontManager::m_Fonts;

		void FontManager::add(Font* font)
		{
			m_Fonts.push_back(font);
		}

		Font* FontManager::get(FontType fontName)
		{
			for (Font* font : m_Fonts)
			{
				if (font->getFont() == fontName)
					return font;
			}

			throw std::runtime_error("Golden Engine 'FontManager::get()' error - no font found");
			return nullptr;
		}

		Font* FontManager::get(FontType fontName, uint16_t size)
		{
			for (Font* font : m_Fonts)
			{
				if (font->getSize() == size && font->getFont() == fontName)
					return font;
			}

			return nullptr;
		}

		void FontManager::remove(FontType fontName)
		{
			for (uint8_t i = 0; i < m_Fonts.size(); i++)
			{
				if (m_Fonts[i]->getFont() == fontName)
				{
					m_Fonts.erase(m_Fonts.begin() + i);
				}
			}
		}
		
		void FontManager::clear()
		{
			m_Fonts.clear();
		}

		void FontManager::printFonts()
		{
			if (m_Fonts.size() == 0)
				std::cout << "empty - no fonts" << std::endl;
			else
			{
				for (uint8_t i = 0; i < m_Fonts.size(); i++)
					std::cout << m_Fonts[i]->getFileName() << std::endl;
			}
		}
	}
}