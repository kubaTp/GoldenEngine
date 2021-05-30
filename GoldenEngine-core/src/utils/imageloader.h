#pragma once

#include <FreeImage.h>

namespace golden {

	static BYTE* load_image(const char* imgPath, GLsizei* width, GLsizei* height)
	{
		//image format
		FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
		//pointer to the image, once loaded
		FIBITMAP* dib = nullptr;

		fif = FreeImage_GetFileType(imgPath, 0);
		if (fif == FIF_UNKNOWN)
			fif = FreeImage_GetFIFFromFilename(imgPath);
		if (fif == FIF_UNKNOWN)
			return nullptr;

		if (FreeImage_FIFSupportsReading(fif))
			dib = FreeImage_Load(fif, imgPath);
		if (!dib)
			return nullptr;

		BYTE* result = FreeImage_GetBits(dib);
		*width = FreeImage_GetWidth(dib);
		*height = FreeImage_GetHeight(dib);

		if ((result == 0) || (width == 0) || (height == 0))
			return nullptr;

		return result;
	}
}
