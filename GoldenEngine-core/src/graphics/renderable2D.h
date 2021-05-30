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
		maths::Vec2 uv; // texture coords
		//unsigned int tid; // texture id
		//maths::Vec4 color;
		unsigned int color;

	};

	class Renderable2D
	{
	protected:
		maths::Vec3 m_Position;
		maths::Vec2 m_Size;
		maths::Vec4 m_Color;
		std::vector<maths::Vec2> m_UV;
	protected:
		Renderable2D() { setDefaultOfUV(); }

	public:
		Renderable2D(maths::Vec3 position, maths::Vec2 size, maths::Vec4 color) : m_Position(position), m_Size(size), m_Color(color) { setDefaultOfUV(); }
		virtual ~Renderable2D() { }

		//reversing : submiting sprite to renderer but in different query
		virtual void submit(Renderer2D* renderer) const { renderer->submit(this); }
		inline const maths::Vec3& getPosition() const { return m_Position; }
		inline const maths::Vec2& getSize() const { return m_Size; }
		inline const maths::Vec4& getColor() const { return m_Color; }
		inline const std::vector<maths::Vec2>& getUV() const { return m_UV; }
	private:
		void setDefaultOfUV() // submit default uv's to the m_UV vector
		{
			m_UV.push_back(maths::Vec2(0, 0));
			m_UV.push_back(maths::Vec2(0, 1));
			m_UV.push_back(maths::Vec2(1, 1));
			m_UV.push_back(maths::Vec2(1, 0));
		}
	};
}}