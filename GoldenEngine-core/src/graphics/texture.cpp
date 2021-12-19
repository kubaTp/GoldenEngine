#include "texture.h"

#include "../utils/imageloader.h"
#include "../utils/assert.h"

namespace golden { namespace graphics {

    Texture::Texture(const std::string& imagePath) : m_ImgPath(imagePath)
    {
        int channels;
        uint8_t* pixels = golden::ImageLoader::loadImage(m_ImgPath, &m_Width, &m_Height, channels);

        #pragma region PIXELS_LOGGING
    #if 0       /// logging all pixels read from image
            for (int i = 0; i < m_Width * m_Height; i += 3)
                std::cout << " pixel - " << static_cast<int>(pixels[i]) << ", " << static_cast<int>(pixels[i + 1]) << ", " << static_cast<int>(pixels[i + 2]) << std::endl;
    #endif
    #pragma endregion
      
        GE_ASSERT(pixels == nullptr, "Golden Engine error: failed to load image at path " + m_ImgPath);

        GLenum internalFormat = GL_RGB, dataFormat = GL_RGB;

        if (channels == 4)
        {
            internalFormat = GL_RGBA;
            dataFormat = GL_RGBA;
        }

        glGenTextures(1, &m_TextureID);
        glBindTexture(GL_TEXTURE_2D, m_TextureID);

        //setting parameters of opengl texture
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); // when minimized setting nearest not linear, "crisp edges" effect
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); // when maximized
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

        glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, m_Width, m_Height, 0, dataFormat, GL_UNSIGNED_BYTE, pixels);

        glBindTexture(GL_TEXTURE_2D, 0);

        ImageLoader::deleteData(pixels);
    }

    Texture::~Texture()
    {
        // TODO : add FreeImage_Unload(dib) -> look if it is not deleting pixels too!
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
