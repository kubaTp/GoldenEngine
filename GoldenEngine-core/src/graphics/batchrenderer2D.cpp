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
		glBindVertexArray(m_VAO); // necessary to bind all attrib pointers to VAO
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

		glBufferData(GL_ARRAY_BUFFER, RENDERER_BUFFER_SIZE, NULL, GL_DYNAMIC_DRAW);

		glEnableVertexAttribArray(SHADER_VERTEX_INDEX);
		glEnableVertexAttribArray(SHADER_UV_INDEX);
		glEnableVertexAttribArray(SHADER_COLOR_INDEX);
		glEnableVertexAttribArray(SHADER_TID_INDEX);

		glVertexAttribPointer(SHADER_VERTEX_INDEX, 3, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*) 0); // 3 bc of 3 floats per vertex and it takes the same size as vertex and the first byte is 0
		glVertexAttribPointer(SHADER_UV_INDEX, 2, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)offsetof(VertexData, VertexData::uv)); // offset to the specified member
		glVertexAttribPointer(SHADER_TID_INDEX, 1, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)offsetof(VertexData, VertexData::tid));
		glVertexAttribPointer(SHADER_COLOR_INDEX, 4, GL_UNSIGNED_BYTE, GL_TRUE, RENDERER_VERTEX_SIZE, (const GLvoid*) offsetof(VertexData, VertexData::color));

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
		const GLuint tid = renderable->getTID();
		 
		unsigned int c = 0;

		// submit verticies -> look at verticies in staticsprite.cpp

		float textureSlot = 0.0f; // textureSlot, sampler should be float, 0 means no texture, 1 means 0 active texture

		if (tid > 0) // if texture id is greater than 1 that means that texture exists
		{
			bool found = false;

			for (int i = 0; i < m_TextureSlots.size(); i++)
			{
				if (m_TextureSlots[i] == tid)
				{
					textureSlot = (float)(i + 1); // grab index to set-up sampler becasue sampler2d works just chronologic, for example tid 6 can be equal to sampler 2 or 3... || (i + 1) because of 0 means no texture and 1 means 0 active texture
					found = true;
					break;
				}
			}

			if (!found)
			{
				if (m_TextureSlots.size() >= 32) // if texture slots are too big
				{
					end();
					flush();
					begin();
				}

				m_TextureSlots.push_back(tid); // if not push back this tid
				textureSlot = (float) (m_TextureSlots.size()); // set textureSlot to the last one in m_TextureSlots
			}
		}
		else
		{
			// color is from 0 to 1 in float
			unsigned char r = color.x * 255.0f;
			unsigned char g = color.y * 255.0f;
			unsigned char b = color.z * 255.0f;
			unsigned char a = color.w * 255.0f;

			c = a << 24 | b << 16 | g << 8 | r; // push alfa to the first bytes
		}


		//0, 0
		m_Buffer->vertex = *m_TransformationStackBack * position;
		m_Buffer->uv = uv[0];
		m_Buffer->tid = textureSlot;
		m_Buffer->color = c;
		m_Buffer++; // advance buffer to the next VertexData

		//0, 5
		m_Buffer->vertex = *m_TransformationStackBack * maths::Vec3(position.x, position.y + size.y, 0);
		m_Buffer->uv = uv[1];
		m_Buffer->tid = textureSlot;
		m_Buffer->color = c;
		m_Buffer++; // advance buffer to the next VertexData

		//5, 5
		m_Buffer->vertex = *m_TransformationStackBack * maths::Vec3(position.x + size.x, position.y + size.y, 0);
		m_Buffer->uv = uv[2];
		m_Buffer->tid = textureSlot;
		m_Buffer->color = c;
		m_Buffer++; // advance buffer to the next VertexData

		//5, 0
		m_Buffer->vertex = *m_TransformationStackBack * maths::Vec3(position.x + size.x, position.y, 0);
		m_Buffer->uv = uv[3];
		m_Buffer->tid = textureSlot;
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
		for (int i = 0; i < m_TextureSlots.size(); i++) // bind every texture in m_TextureSlots
		{
			glActiveTexture(GL_TEXTURE0 + i);
			glBindTexture(GL_TEXTURE_2D, m_TextureSlots[i]);
		}

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