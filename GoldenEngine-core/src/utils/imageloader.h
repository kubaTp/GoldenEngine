#pragma once

#include <FreeImage.h>

namespace golden {

	static BYTE* load_image(const char* imgPath, GLsizei* width, GLsizei* height, uint8_t* channels)
	{
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

		BYTE* pixels = FreeImage_GetBits(dib);
		*width = FreeImage_GetWidth(dib);
		*height = FreeImage_GetHeight(dib);
		unsigned bytespp = FreeImage_GetLine(dib) / *width; // FreeImage_GetLine() - returns the width of the bitmap in bytes
		*channels = bytespp / sizeof(pixels[0]);
		int32_t bits= FreeImage_GetBPP(dib); // returns bits so need to be divided by 8

		int32_t size = *width * *height * (bits / 8);
		BYTE* result = new BYTE[size];

		memcpy(result, pixels, size);

		if ((result == 0))
			return nullptr;

		FreeImage_Unload(dib);
		return result;
	}
}
