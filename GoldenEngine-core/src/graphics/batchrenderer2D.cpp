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
		glDeleteVertexArrays(1, &m_VAO);
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
		glEnableVertexAttribArray(SHADER_UV_INDEX);
		glEnableVertexAttribArray(SHADER_COLOR_INDEX);
		
		glVertexAttribPointer(SHADER_VERTEX_INDEX, 3, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*) 0); // 3 bc of 3 floats per vertex and it takes the same size as vertex and the first byte is 0
		glVertexAttribPointer(SHADER_UV_INDEX, 2, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)offsetof(VertexData, VertexData::uv));
		glVertexAttribPointer(SHADER_COLOR_INDEX, 4, GL_UNSIGNED_BYTE, GL_TRUE, RENDERER_VERTEX_SIZE, (const GLvoid*) offsetof(VertexData, VertexData::color)); //3 * 4 = 12, it is the first bit of color

		glBindBuffer(GL_ARRAY_BUFFER, 0);

		/*construct indicies for 10k sprites*/
		GLuint* indicies = new GLuint[RENDERER_INDICIES_SIZE];
		
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
		const std::vector<maths::Vec2>& uv = renderable->getUV();

		/*submit verticies -> look at verticies in staticsprite.cpp*/

		//color is from 0 to 1 in float
		unsigned char r = color.x * 255.0f;
		unsigned char g = color.y* 255.0f;
		unsigned char b = color.z * 255.0f;
		unsigned char a = color.w * 255.0f;

		unsigned int c = a << 24 | b << 16 | g << 8 | r; //push alfa to the first bytes


		//0, 0
		m_Buffer->vertex = *m_TransformationStackBack * position;
		m_Buffer->uv = uv[0];
		m_Buffer->color = c;
		m_Buffer++; // advance buffer to the next VertexData

		//0, 5
		m_Buffer->vertex = *m_TransformationStackBack * maths::Vec3(position.x, position.y + size.y, 0);
		m_Buffer->uv = uv[1];
		m_Buffer->color = c;
		m_Buffer++; // advance buffer to the next VertexData

		//5, 5
		m_Buffer->vertex = *m_TransformationStackBack * maths::Vec3(position.x + size.x, position.y + size.y, 0);
		m_Buffer->uv = uv[2];
		m_Buffer->color = c;
		m_Buffer++; // advance buffer to the next VertexData

		//5, 0
		m_Buffer->vertex = *m_TransformationStackBack * maths::Vec3(position.x + size.x, position.y, 0);
		m_Buffer->uv = uv[3];
		m_Buffer->color = c;
		m_Buffer++; // advance buffer to the next VertexData

		//add new 6 verticies
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

		//draw amount of verticies given in m_IndexCount variable 
		glDrawElements(GL_TRIANGLES, m_IndexCount, GL_UNSIGNED_INT, NULL);

		glBindVertexArray(0);
		m_IBO->unbind();

		//make m_IndexCount 0 for next draw call
		m_IndexCount = 0;
	}
}}