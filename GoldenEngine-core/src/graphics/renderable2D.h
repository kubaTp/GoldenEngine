#pragma once

#include "buffers/buffer.h"
#include "buffers/indexbuffer.h"
#include "buffers/vertexarray.h"

#include "../maths/maths.h"
#include "shader.h"

#include "renderer2D.h"


namespace golden { namespace graphics {

	struct VertexData //one vertex, sprite has 4 verticies
	{
		maths::Vec3 vertex;
		unsigned int color;
		//maths::Vec4 color;
	};

	class Renderable2D
	{
	protected:
		maths::Vec3 m_Position;
		maths::Vec2 m_Size;
		maths::Vec4 m_Color;
	protected:
		Renderable2D() { }
	public:
		Renderable2D(maths::Vec3 position, maths::Vec2 size, maths::Vec4 color) : m_Position(position), m_Size(size), m_Color(color) { }
		virtual ~Renderable2D() { }

		virtual void submit(Renderer2D* renderer) const { renderer->submit(this); }

		inline const maths::Vec3& getPosition() const { return m_Position; }
		inline const maths::Vec2& getSize() const { return m_Size; }
		inline const maths::Vec4& getColor() const { return m_Color; }
	};
}}