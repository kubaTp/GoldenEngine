#include "batchrenderer2D.h"

namespace golden { namespace graphics {

	BatchRenderer2D::BatchRenderer2D()
	{
		init();
	}

	BatchRenderer2D::~BatchRenderer2D()
	{
		delete m_IBO;

		glDeleteBuffers(1, &m_VBO);
		//glDeleteVertexArrays(1, &m_VAO);
	}

	void BatchRenderer2D::init()
	{
		/*VAO - bind vertex array*/
		/*VBO - bind general buffer*/
		glGenVertexArrays(1, &m_VAO);
		glGenBuffers(1, &m_VBO);
		glBindVertexArray(m_VAO);//necessary to bind all attrib pointers to VAO
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

		glBufferData(GL_ARRAY_BUFFER, RENDERER_BUFFER_SIZE, NULL, GL_DYNAMIC_DRAW);

		glEnableVertexAttribArray(SHADER_VERTEX_INDEX);
		glEnableVertexAttribArray(SHADER_COLOR_INDEX);

		glVertexAttribPointer(SHADER_VERTEX_INDEX, 3, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*) 0); // 3 bc of 3 floats per vertex and it takes the same size as vertex and the firs byte is 0
		glVertexAttribPointer(SHADER_COLOR_INDEX, 4, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*) (3 * sizeof(GLfloat))); //3 * 4 = 12, it is the first bit of color
		
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		/*construct indicies for 10k sprites*/
		GLushort indicies[RENDERER_INDICIES_SIZE];

		int offset = 0;
		for (int i = 0; i < RENDERER_INDICIES_SIZE; i+= 6)
		{
			indicies[i] = offset + 0;
			indicies[i + 1] = offset + 1;
			indicies[i + 2] = offset + 2;

			indicies[i + 3] = offset + 2;
			indicies[i + 4] = offset + 3;
			indicies[i + 5] = offset + 0;

			offset += 4;
		}

		m_IBO = new IndexBuffer(indicies, RENDERER_INDICIES_SIZE); //count = 60k

		glBindVertexArray(0);
	}

	void BatchRenderer2D::begin()
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		m_Buffer = (VertexData*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
	}

	void BatchRenderer2D::submit(const Renderable2D* renderable)
	{
		const maths::Vec2& size = renderable->getSize();
		const maths::Vec3& position = renderable->getPosition();
		const maths::Vec4& color = renderable->getColor();

		/*submit verticies -> look at verticies in staticsprite.cpp*/

		//0, 0
		m_Buffer->vertex = position;
		m_Buffer->color = color;
		m_Buffer++; // advance buffer to the next VertexData

		//0, 5
		m_Buffer->vertex = maths::Vec3(position.x, position.y + size.y, 0);
		m_Buffer->color = color;
		m_Buffer++; // advance buffer to the next VertexData

		//5, 5
		m_Buffer->vertex = maths::Vec3(position.x + size.x, position.y + size.y, 0);
		m_Buffer->color = color;
		m_Buffer++; // advance buffer to the next VertexData

		//5, 0
		m_Buffer->vertex = maths::Vec3(position.x + size.x, position.y, 0);
		m_Buffer->color = color;
		m_Buffer++; // advance buffer to the next VertexData

		m_IndexCount += 6;
	}
	
	void BatchRenderer2D::end()
	{
		glUnmapBuffer(GL_ARRAY_BUFFER);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void BatchRenderer2D::flush()
	{
		glBindVertexArray(m_VAO);
		m_IBO->bind();

		glDrawElements(GL_TRIANGLES, m_IndexCount, GL_UNSIGNED_SHORT, NULL);

		glBindVertexArray(0);
		m_IBO->unbind();

		m_IndexCount = 0;
	}
}}