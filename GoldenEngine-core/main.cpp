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

#include "src/graphics/staticsprite.h"
#include "src/graphics/sprite.h"
#include "src/utils/timer.h"

#include "time.h"

#include "src/graphics/layers/tilelayer.h"

#include "src/graphics/layers/group.h"

#define BATCH_RENDERER 1
#define MAX_SPRITE_AMOUNT 1

int main()
{
	using namespace golden;
	using namespace graphics;
	using namespace maths;

	Window window("Golden Engine", 960.0f, 540.0f);
	window.clear();

	Mat4 ortho = Mat4::orthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f);

	Shader shader("src/shaders/basic.vert", "src/shaders/basic.frag");
	Shader shader2("src/shaders/basic.vert", "src/shaders/basic.frag");
	shader.enable();
	shader.setUniform2f("light_pos", Vec2(0, 0));
	shader2.enable();
	shader2.setUniform2f("light_pos", Vec2(0, 0));

	TileLayer layer(shader);

#if MAX_SPRITE_AMOUNT
	for (float y = -9.0f; y < 9.0f; y += 0.1f)
	{
		for (float x = -16.0f; x < 16.0f; x += .1f)
		{
			layer.add(new Sprite(x, y, 0.09f, 0.09f, maths::Vec4(1, rand() % 1000 / 1000.0f, 0, 1)));
		}
	}
#else
#if 0
	for (float y = -9.0f; y < 9.0f; y++)
	{
		for (float x = -16.0f; x < 16.0f; x++)
		{
			layer.add(new Sprite(x, y, 0.9f, 0.9f, maths::Vec4(1, rand() % 1000 / 1000.0f, 0, 1)));
		}
	}
#endif
	layer.add(new Sprite(-15.0f, 5.0f, 6, 3, maths::Vec4(1, 1, 1, 1)));
	layer.add(new Sprite(0.5f, 0.5f, 5.5f, 2.0f, maths::Vec4(1, 1, 1, 1)));
#endif

	TileLayer layer2(shader2);
	layer2.add(new Sprite(-2, -2, 4, 4, maths::Vec4(0.2f, 0.8f, 0.6f, 1.0f)));

	Timer currentTime, timer;
	short frameCounter = 0;

	while (!window.closed())
	{
		window.clear();
		frameCounter++;

		double x, y;
		window.getMousePosition(x, y);

#if 1
		shader.enable();
		//shader.setUniform2f("light_pos", Vec2(-10, -4.5f));
		//shader2.enable();
		shader.setUniform2f("light_pos", Vec2((float)(x * 32.0f / window.getWidth() - 16.0f), (float)(9.0f - y * 18.0f / window.getHeight())));
#endif

		layer.render();
		//layer2.render();

		window.update();

		/*display fps*/
		if (currentTime.elapsed() > 1.0f) // every second
		{
			printf("fps: %d\n", frameCounter);
			frameCounter = 0;
			currentTime.reset();
		}
	}

	return 0;
} 