#include "font.h"

namespace golden {
	namespace graphics {

		Font::Font(FontType font, const std::string& filename, uint16_t size)
			: m_Font(font), m_Filename(filename), m_Size(size)
		{
			// upload atlas and font
			m_FTatlas = ftgl::texture_atlas_new(512, 512, 2);
			m_FTfont = ftgl::texture_font_new_from_file(m_FTatlas, m_Size, m_Filename.c_str());
			ftgl::texture_atlas_upload(m_FTatlas);
		}

		Font::Font(const std::string& filename, uint16_t size)
			: m_Font(FontType::Unknown), m_Filename(filename), m_Size(size)
		{
			// upload atlas and font
			m_FTatlas = ftgl::texture_atlas_new(512, 512, 2);
			m_FTfont = ftgl::texture_font_new_from_file(m_FTatlas, m_Size, m_Filename.c_str());
			ftgl::texture_atlas_upload(m_FTatlas);
		}
	}
}