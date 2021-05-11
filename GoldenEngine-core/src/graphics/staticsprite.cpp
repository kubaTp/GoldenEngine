#include "staticsprite.h"

namespace golden { namespace graphics {

	StaticSprite::StaticSprite(float x, float y, float width, float height, const maths::Vec4& color, Shader& shader) 
		: Renderable2D(maths::Vec3(x, y, 0), maths::Vec2(width, height), color), m_Shader(shader)
	{
		m_VertexArray = new VertexArray();

		GLfloat verticies[]
		{
			0, 0, 0,
			0, height, 0,
			width, height, 0,
			width, 0, 0
		};

		GLfloat colors[]
		{
			color.x, color.y, color.z, color.w,
			color.x, color.y, color.z, color.w,
			color.x, color.y, color.z, color.w,
			color.x, color.y, color.z, color.w
		};

		m_VertexArray->addBuffer(new Buffer(verticies, 4 * 3, 3), 0);
		m_VertexArray->addBuffer(new Buffer(colors, 4 * 4, 4), 1);

		GLushort indicies[] = { 0, 1, 2, 2, 3, 0 };
		m_IndexBuffer = new IndexBuffer(indicies, 6);
	}

	StaticSprite::~StaticSprite()
	{
		delete m_VertexArray, m_IndexBuffer, m_Shader;
	}
}}