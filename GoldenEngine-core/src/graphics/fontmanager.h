#pragma once

#include <iostream>
#include <vector>
#include "font.h"

namespace golden { namespace graphics {
		
	static class FontManager
	{
	public:
		static void add(Font* font);
		static Font* get(FontType fontName);
		static Font* get(FontType fontName, uint16_t size);
		static void remove(FontType fontName);
		static void clear();

		static void printFonts();
	private:
		static std::vector<Font*> m_Fonts;
	};
}}