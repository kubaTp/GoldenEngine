#pragma once

#include <GL/glew.h>

#include <cstdint>
#include <string>

#include "../../extLibs/stb-image/stb_image.h"

namespace golden {

	static struct ImageLoader
	{
		static uint8_t* loadImage(std::string& imgPath, GLsizei* width, GLsizei* height, int& channels)
		{
			stbi_set_flip_vertically_on_load(1);
			return stbi_load(imgPath.c_str(), width, height, &channels, 0);
		}

		static uint8_t* loadImageNeutral(std::string& imgPath, GLsizei* width, GLsizei* height, int& channels)
		{
			return stbi_load(imgPath.c_str(), width, height, &channels, 0);
		}

		static uint8_t* loadImageNeutralWithoutChannel(const std::string& imgPath, GLsizei* width, GLsizei* height)
		{
			return stbi_load(imgPath.c_str(), width, height, 0, 0);
		}

		static void deleteData(uint8_t* data)
		{
			stbi_image_free(data);
		}
	};
}
