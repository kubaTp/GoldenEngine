#pragma once

#include <string>
#include <stdint.h>
#include <stdexcept>

#include "../../extLibs/freetype-gl/freetype-gl.h"

namespace golden { namespace graphics {

	enum struct FontType { Inter_Regular, Jura, Arial, SourceSerifPro, Unknown };

	class Font
	{
	public:
		Font(FontType font, const std::string& filename, uint16_t size);
		Font(const std::string& filename, uint16_t size);

		inline ftgl::texture_atlas_t* getFTGLAtlas() const { return m_FTatlas; }
		inline ftgl::texture_font_t* getFTGLFont() const { return m_FTfont; }
		inline const FontType getFont() const { return m_Font; }
		inline const std::string& getFileName() const { return m_Filename; }
		inline const uint16_t& getSize() const { return m_Size; }

		friend static class FontManager;
	private:
		FontType m_Font;
		std::string m_Filename;
		uint16_t m_Size;

		ftgl::texture_atlas_t* m_FTatlas;
		ftgl::texture_font_t* m_FTfont;
	};
}}