#include "src/graphics/window.h"
#include "src/graphics/shader.h"
#include "src/maths/maths.h"
#include "src/utils/fileutils.h"

int main()
{
	using namespace golden;
	using namespace graphics;
	using namespace maths;

	Window window("Golden!", 960, 540);
	glClearColor(0.2f, 0.3f, 0.8f, 1.0f);

	GLfloat verticies[] =
	{
		-2, -2, 0,
		-2,  2, 0,
		 2,  2, 0,
		 2, -2, 0
	};

	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticies), verticies, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	Mat4 ortho = Mat4::orthographic(-9.0f, 9.0f, -9.0f, 9.0f, -1.0f, 1.0f);

	Shader shader("src/shaders/basic.vert", "src/shaders/basic.frag");
	shader.enable();
	shader.setUniformMat4("pr_matrix", ortho);
	shader.setUniformMat4("ml_matrix", Mat4::rotation(180.0f, Vec3(0, 1, 0)));

	while (!window.closed())
	{
		window.clear();
#if 0
		glBegin(GL_QUADS);
		glVertex2f(-0.5f, -0.5f);
		glVertex2f(-0.5f, 0.5f);
		glVertex2f(0.5f, 0.5f);
		glVertex2f(0.5f, -0.5f);
		glEnd();
#else
		glDrawArrays(GL_QUADS, 0, 4);
#endif

		window.update();
	}

	return 0;
}