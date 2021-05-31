#pragma once

#include <GL/glew.h>
#include <FreeImage.h>

#include <string>
#include "../utils/imageloader.h"

namespace golden { namespace graphics {

	class Texture
	{
	private:
		std::string m_ImgPath;
		GLuint m_TextureID; // also called m_TID => Texture ID
		GLsizei m_Width, m_Height;

	public:
		Texture(const std::string& imagePath);
		~Texture();

		void bind() const; // bind texture
		void unbind() const; // unbind texture

		inline const GLsizei getWidth() const { return m_Width; }
		inline const GLsizei getHeight() const { return m_Height; }
		inline const GLuint getTextureID() const { return m_TextureID; }
	private:
		GLuint load();
	};
}}