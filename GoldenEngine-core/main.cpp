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

#include "time.h"

#define BATCH_RENDERER 0

int main()
{
	using namespace golden;
	using namespace graphics;
	using namespace maths;

	Window window("Golden Engine", 960.0f, 540.0f);

#if 0
	GLfloat verticies[] =
	{
		 0, 0, 0,
		 0, 3, 0,
		 8, 3, 0,
		 8, 0, 0
	};

	GLushort indicies[] =
	{
		0, 1, 2,
		2, 3, 0
	};

	GLfloat colors1[] =
	{
		1, 0, 1, 1,
		1, 0, 1, 1,
		0, 1, 1, 1,
		1, 1, 1, 1
	};

	GLfloat colors2[] =
	{
		0.2f, 0.3f, 0.8f, 1,
		0.1f, 0.1f, 0.4f, 1,
		0.9f, 0.1f, 0.3f, 1,
		0.6f, 0.6f, 0.8f, 1
	};

	VertexArray vao, vao2;
	IndexBuffer ibo(indicies, 6);

	vao.addBuffer(new Buffer(verticies, 4 * 3, 3), 0); //3 bc of vec3
	vao.addBuffer(new Buffer(colors1, 4 * 4, 4), 1); //4 bc of vec4

	vao2.addBuffer(new Buffer(verticies, 4 * 3, 3), 0);
	vao2.addBuffer(new Buffer(colors2, 4 * 4, 4), 1);
#endif

	Mat4 ortho = Mat4::orthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f);

	Shader shader("src/shaders/basic.vert", "src/shaders/basic.frag");
	shader.enable();
	shader.setUniformMat4("pr_matrix", ortho);
	shader.setUniform2f("light_pos", Vec2(0, 0));

	Sprite sprite1(5, 5, 4, 4, maths::Vec4(1, 0, 1, 1));
	Sprite sprite2(5, 1, 2, 3, maths::Vec4(0.2f, 0, 1, 1));
	BatchRenderer2D renderer;

	while (!window.closed())
	{
		window.clear();

		double x, y;
		window.getMousePosition(x, y);
		shader.setUniform2f("light_pos", Vec2((float)(x * 16.0f / 960.0f), (float)(9.0f - y * 9.0f / 540.0f)));
#if 1
		renderer.begin();
		renderer.submit(&sprite1);
		renderer.submit(&sprite2);
		renderer.end();
		renderer.flush();

#else
		vao.bind();
		ibo.bind();
		shader.setUniformMat4("ml_matrix", Mat4::translation(Vec3(4, 3, 0)));
		glDrawElements(GL_TRIANGLES, ibo.getCount(), GL_UNSIGNED_SHORT, 0);
		vao.unbind();
		ibo.unbind();

		vao2.bind();
		ibo.bind();
		shader.setUniformMat4("ml_matrix", Mat4::translation(Vec3(0, 0, 0)));
		glDrawElements(GL_TRIANGLES, ibo.getCount(), GL_UNSIGNED_SHORT, 0);
		vao2.unbind();
		ibo.unbind();
#endif
		window.update();
	}
	return 0;
}