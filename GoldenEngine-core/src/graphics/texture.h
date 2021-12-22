#pragma once

#include <GL/glew.h>

#include <iostream>
#include <string>

#include "../../extLibs/stb-image/stb_image.h"
#include "../../extLibs/json_struct/json_struct.h"

namespace golden  { namespace graphics {

	class Texture
	{
	private:
		std::string m_ImgPath; // serialize
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
		inline const std::string getImagePath() const { return m_ImgPath; }
	};

	struct TextureSpec
	{
		std::string imagePath;
		TextureSpec() : imagePath("empty path") { }

		Texture& convertToTexture() const
		{
			Texture* newTexture = new Texture(imagePath);
			return *newTexture;
		}

		JS_OBJECT(JS_MEMBER_WITH_NAME(imagePath, "ImgPath"));
	};
}}
