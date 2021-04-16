#include "src/graphics/window.h"
#include "src/maths/maths.h"

int main()
{
	using namespace golden;
	using namespace graphics;
	using namespace maths;

#if 1
	Window window("Golden!", 960, 540);
	glClearColor(0.2f, 0.3f, 0.8f, 1.0f);

	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	Vec4 a(1.0f, 2.0f, 5.0f, 2.0f);
	Vec4 b(2, 4, 3, 3);

	Vec4 c = a + b;

	Mat4 position = Mat4::translation(Vec3(2, 3, 4));
	position *= Mat4::idenity();
	
	position.elements[12] = 2.0f;

	Vec4 c0 = position.columns[3];

	//std::cout << &position.elements[12] << std::endl;
	//std::cout << &c1 << std::endl;

	std::cout << "union: " << c0 << std::endl;
	
	while (!window.closed())
	{
		//std::cout << c << std::endl;
		window.clear();
#if 1
		glBegin(GL_QUADS);
		glVertex2f(-0.5f, -0.5f);
		glVertex2f(-0.5f, 0.5f);
		glVertex2f(0.5f, 0.5f);
		glVertex2f(0.5f, -0.5f);
		glEnd();
#else
		glDrawArrays(GGL_ARRAY_BUFFER, 0, 6);
#endif
		window.update();
	}
#endif
		return 0;
}