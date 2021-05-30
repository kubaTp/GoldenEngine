#include "src/graphics/window.h"
#include "src/graphics/shader.h"
#include "src/maths/maths.h"
#include "src/utils/fileutils.h"

//TODO : make for example buffer_pack.h where all buffers will be included

#include "src/graphics/buffers/buffer.h"
#include "src/graphics/buffers/indexbuffer.h"
#include "src/graphics/buffers/vertexarray.h"

#include "src/graphics/simple2Drenderer.h"
#include "src/graphics/batchrenderer2D.h"

#include "time.h"
#include "src/utils/timer.h"

#include "src/graphics/staticsprite.h"
#include "src/graphics/sprite.h"
#include "src/graphics/texture.h"

#include "src/graphics/layers/tilelayer.h"
#include "src/graphics/layers/group.h"

#define endl '\n'

#define BATCH_RENDERER 1
#define MAX_SPRITE_AMOUNT 0

// TODO : experiment with the shaders and set up them

#pragma region IMAGE_LOADING_TEST
#if 0
int main()
{
	const char* filename = "img/test_2_24BIT.png";

	//image format
	FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
	//pointer to the image, once loaded
	FIBITMAP* dib(0);
	//pointer to the image data
	BYTE* bits(0);
	//image width and height
	unsigned int width(0), height(0);
	//OpenGL's image ID to map to
	GLuint gl_texID;

	//check the file signature and deduce its format
	fif = FreeImage_GetFileType(filename, 0);
	//if still unknown, try to guess the file format from the file extension
	if (fif == FIF_UNKNOWN)
		fif = FreeImage_GetFIFFromFilename(filename);

	//check that the plugin has reading capabilities and load the file
	if (FreeImage_FIFSupportsReading(fif))
		dib = FreeImage_Load(fif, filename);


	bits = FreeImage_GetBits(dib);

	width = FreeImage_GetWidth(dib);
	height = FreeImage_GetHeight(dib);
	 
	unsigned short bitsPerPixel = FreeImage_GetBPP(dib);
	unsigned int pitch = FreeImage_GetPitch(dib);

	std::cout << "w: " << width << ", h: " << height << ", bpp: " <<  bitsPerPixel << endl;

	for (int y = 0; y < height; y++) 
	{
		BYTE* pixel = (BYTE*)bits; 
		for (int x = 0; x < width; x++)
		{
			std::cout << +pixel[FI_RGBA_RED] << " " << +pixel[FI_RGBA_GREEN] << " " << +pixel[FI_RGBA_BLUE] << endl;
			pixel += 3;
		}
		bits += pitch;
	}

	FreeImage_Unload(dib);

	return 0;
}
#endif
#pragma endregion

#if 1

int main()
{
	using namespace golden;
	using namespace graphics;
	using namespace maths;

	Window window("Golden Engine", 960.0f, 540.0f);
	window.clear();

	// projection matrix is maths::Mat4::orthographic(-16.0f, 16.0f, -9.0f, 9.0f, 1.0f, -1.0f)

	Shader shader("src/shaders/basic.vert", "src/shaders/basic.frag");
	shader.enable();
	shader.setUniform2f("light_pos", Vec2(0, 0));

	TileLayer layer(shader); // layer of sprites

	#pragma region MAX_SPRITE_AMOUNT

	#if MAX_SPRITE_AMOUNT
		for (float y = -9.0f; y < 9.0f; y += 0.1f)
		{
			for (float x = -16.0f; x < 16.0f; x += .1f)
			{
				layer.add(new Sprite(x, y, 0.09f, 0.09f, maths::Vec4(1, rand() % 1000 / 1000.0f, 0, 1)));
			}
		}
	#else
		for (float y = -9.0f; y < 9.0f; y++)
		{
			for (float x = -16.0f; x < 16.0f; x++)
			{
				layer.add(new Sprite(x, y, 0.9f, 0.9f, maths::Vec4(1, rand() % 1000 / 1000.0f, 0, 1)));
			}
		}

	#endif

#pragma endregion

	Texture texture("img/24Bit_img.png");
	texture.bind();

	glActiveTexture(GL_TEXTURE0);

	shader.enable();
	shader.setUniform1f("tex", 0);

	Timer timer;
	short frameCounter = 0, deltaTime = 0;
	// GAME LOOP
	while (!window.closed())
	{
		// SOME TEXTURES :(

		window.clear();
		frameCounter++;

		shader.enable();
		double x, y;
		window.getMousePosition(x, y);

		shader.enable();
		shader.setUniform2f("light_pos", Vec2((float)(x * 32.0f / window.getWidth() - 16.0f), (float)(9.0f - y * 18.0f / window.getHeight())));

		layer.render(); // submits new sprites and draw it, sprites are stored in layer

		window.update();
		/*display fps*/
		if (timer.elapsed() - deltaTime > 1.0f) // every second
		{
			//printf("fps: %d\n", frameCounter);

			frameCounter = 0;
			deltaTime++;
		}
	}

	return 0;
}

#endif