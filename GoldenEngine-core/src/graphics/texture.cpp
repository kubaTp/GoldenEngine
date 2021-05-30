#include "texture.h"

namespace golden { namespace graphics {

	Texture::Texture(const std::string& imagePath) : m_ImgPath(imagePath)
	{
		m_TextureID = load();
	}

	Texture::~Texture()
	{
		// TODO : add FreeImage_Unload(dib) -> look if it is not deleting pixels too!
	}

	GLuint Texture::load() 
	{
		BYTE* pixels = load_image(m_ImgPath.c_str(), &m_Width, &m_Height);

		GLuint result; // result which will be returning by this function
		glGenTextures(1, &result);
		glBindTexture(GL_TEXTURE_2D, result);

		//setting parameters of opengl texture
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); // "crispEdges"
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_Width, m_Height, 0, GL_BGR, GL_UNSIGNED_BYTE, pixels);

		glBindTexture(GL_TEXTURE_2D, 0);

		return result;
	}

	void Texture::bind() const
	{
		glBindTexture(GL_TEXTURE_2D, m_TextureID);
	}
	
	void Texture::unbind() const
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}}