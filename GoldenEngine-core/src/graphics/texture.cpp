#include "texture.h"

namespace golden {
	namespace graphics {
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
			uint8_t channels;
			BYTE* pixels = load_image(m_ImgPath.c_str(), &m_Width, &m_Height, &channels);
			GLenum internalFormat = GL_RGB8, dataFormat = GL_BGR;

			if (channels == 4)
			{
				internalFormat = GL_RGBA8;
				dataFormat = GL_BGRA;
			}

			GLuint result; // result which will be returning by this function, TID
			glGenTextures(1, &result);
			glBindTexture(GL_TEXTURE_2D, result);

			//setting parameters of opengl texture
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); // when minimized setting nearest not linear, "crisp edges" effect
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); // when maximized

			glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, m_Width, m_Height, 0, dataFormat, GL_UNSIGNED_BYTE, pixels);

			glBindTexture(GL_TEXTURE_2D, 0);

			delete[] pixels;

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
	}
}