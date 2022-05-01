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

		glBufferData(GL_ARRAY_BUFFER, RENDERER_BUFFER_SIZE, NULL, GL_DYNAMIC_DRAW); // sprite size * how many sprites

		glEnableVertexAttribArray(SHADER_VERTEX_INDEX); // 0
		glEnableVertexAttribArray(SHADER_UV_INDEX);		// 1
		glEnableVertexAttribArray(SHADER_COLOR_INDEX);	// 2
		glEnableVertexAttribArray(SHADER_TID_INDEX);	// 3

		glVertexAttribPointer(SHADER_VERTEX_INDEX, 3, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)0); // 3 bc of 3 floats per vertex and it takes the same size as vertex and the first byte is 0
		glVertexAttribPointer(SHADER_UV_INDEX, 2, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)offsetof(VertexData, VertexData::uv)); // offset to the specified member
		glVertexAttribPointer(SHADER_TID_INDEX, 1, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)offsetof(VertexData, VertexData::tid));
		glVertexAttribPointer(SHADER_COLOR_INDEX, 4, GL_UNSIGNED_BYTE, GL_TRUE, RENDERER_VERTEX_SIZE, (const GLvoid*)offsetof(VertexData, VertexData::color));

		glBindBuffer(GL_ARRAY_BUFFER, 0);

		/*construct indicies for 10k sprites*/
		GLuint* indicies = new GLuint[RENDERER_INDICIES_SIZE];

		int offset = 0;
		for (int i = 0; i < RENDERER_INDICIES_SIZE; i += 6)
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

		glBindVertexArray(0); // unbinding at the end
	}

	void BatchRenderer2D::begin()
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		m_Buffer = (VertexData*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
	}

	void BatchRenderer2D::submit(const Renderable2D* renderable)
	{		
		std::shared_ptr<ecs::TransformComponent> transform = renderable->getComponent<ecs::TransformComponent>();

		const maths::Vec2& size = maths::Vec2(transform->scale.x, transform->scale.y);
		const maths::Vec3& position = transform->position;

		const uint32_t color = renderable->getColor(); //const uint32_t color = 0xffffffff;
		const std::vector<maths::Vec2>& uv = renderable->getUV();
		const GLuint tid = renderable->getTID();

		float textureSlot = 0.0f; // textureSlot, sampler should be float, 0 means no texture, other means other active texture

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
				textureSlot = (float)(m_TextureSlots.size()); // set textureSlot to the last one in m_TextureSlots
			}
		}

		// submit verticies -> look at verticies in staticsprite.cpp

		//0, 0
		
		m_Buffer->vertex = *m_TransformationStackBack * position;
		m_Buffer->uv = uv[0];
		m_Buffer->tid = textureSlot;
		m_Buffer->color = color;
		m_Buffer++; // advance buffer to the next VertexData

		//0, 5
		m_Buffer->vertex = *m_TransformationStackBack * maths::Vec3(position.x, position.y + size.y, 0);
		m_Buffer->uv = uv[1];
		m_Buffer->tid = textureSlot;
		m_Buffer->color = color;
		m_Buffer++; // advance buffer to the next VertexData

		//5, 5
		m_Buffer->vertex = *m_TransformationStackBack * maths::Vec3(position.x + size.x, position.y + size.y, 0);
		m_Buffer->uv = uv[2];
		m_Buffer->tid = textureSlot;
		m_Buffer->color = color;
		m_Buffer++; // advance buffer to the next VertexData

		//5, 0
		m_Buffer->vertex = *m_TransformationStackBack * maths::Vec3(position.x + size.x, position.y, 0);
		m_Buffer->uv = uv[3];
		m_Buffer->tid = textureSlot;
		m_Buffer->color = color;
		m_Buffer++; // advance buffer to the next VertexData

		//add new 6 verticies
		m_IndexCount += 6;
	}

	void BatchRenderer2D::drawString(const std::string& text, const maths::Vec3& position, const Font& font, const uint32_t color)
	{
		using namespace ftgl;

		bool found = false;
		float ts = 0.0f;

		for (int i = 0; i < m_TextureSlots.size(); i++)
		{
			if (m_TextureSlots[i] == font.getFTGLAtlas()->id)
			{
				ts = (float)(i + 1); // grab index to set-up sampler becasue sampler2d works just chronologic, for example tid 6 can be equal to sampler 2 or 3... ||
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

			m_TextureSlots.push_back(font.getFTGLAtlas()->id); // if not push back this tid
			ts = (float)(m_TextureSlots.size()); // set textureSlot to the last one in m_TextureSlots
		}

		maths::Vec2 scale = maths::Vec2(2000.0f / 32.0f, 
									    1200.0f / 16.0f);

		float x = position.x;

		texture_font_t* ftFont = font.getFTGLFont();

		for (uint16_t i = 0; i < text.length(); i++)
		{
			texture_glyph_t* glyph = texture_font_get_glyph(ftFont, text[i]);

			if (text[i] == 'P')
			{
				//std::cout << glyph->offset_x / scale.x << std::endl;
			}

			if (glyph)
			{
				if (i > 0)
				{
					float kerning = texture_glyph_get_kerning(glyph, text[i - 1]);
					x += kerning / scale.x;
				}

				float x0 = x + glyph->offset_x / scale.x;
				float y0 = position.y + glyph->offset_y / scale.y;
				float x1 = x0 + glyph->width / scale.x;
				float y1 = y0 - glyph->height / scale.y; // projection matrix has positive top so needs to be substract
				
				float u0 = glyph->s0;
				float v0 = glyph->t0;
				float u1 = glyph->s1;
				float v1 = glyph->t1;

				m_Buffer->vertex = maths::Vec3(x0, y0, 0);
				m_Buffer->uv = maths::Vec2(u0, v0);
				m_Buffer->tid = ts;
				m_Buffer->color = color;
				m_Buffer++; // advance buffer to the next VertexData

				m_Buffer->vertex = maths::Vec3(x0, y1, 0);
				m_Buffer->uv = maths::Vec2(u0, v1);
				m_Buffer->tid = ts;
				m_Buffer->color = color;
				m_Buffer++; // advance buffer to the next VertexData

				m_Buffer->vertex = maths::Vec3(x1, y1, 0);
				m_Buffer->uv = maths::Vec2(u1, v1);
				m_Buffer->tid = ts;
				m_Buffer->color = color;
				m_Buffer++; // advance buffer to the next VertexData

				m_Buffer->vertex = maths::Vec3(x1, y0, 0);
				m_Buffer->uv = maths::Vec2(u1, v0);
				m_Buffer->tid = ts;
				m_Buffer->color = color;
				m_Buffer++; // advance buffer to the next VertexData

				m_IndexCount += 6;

				x += glyph->advance_x / scale.x;
			}
		}
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