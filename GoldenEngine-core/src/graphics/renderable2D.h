#pragma once

#include "buffers/buffer.h"
#include "buffers/indexbuffer.h"
#include "buffers/vertexarray.h"

#include "../maths/maths.h"
#include "shader.h"

#include "renderer2D.h"

#include "texture.h"

namespace golden { namespace graphics {

	struct VertexData // struct represents one of 4 vertex in one sprite
	{
		maths::Vec3 vertex;
		maths::Vec2 uv; // texture coords
		float tid; // texture id
		//maths::Vec4 color;
		unsigned int color;
	};

	class Renderable2D
	{
	protected:
		maths::Vec3 m_Position; // position given
		maths::Vec2 m_Size; // size of renderable
		maths::Vec4 m_Color; // color of renderable
		std::vector<maths::Vec2> m_UV; // texture coords

		Texture* m_Texture; // pointer to texture, because everyone renderable has "own" texture
	protected:
		Renderable2D() { setDefaultOfUV(); } // set default texture coords

	public:
		Renderable2D(maths::Vec3 position, maths::Vec2 size, maths::Vec4 color) : m_Position(position), m_Size(size), m_Color(color) { setDefaultOfUV(); }
		virtual ~Renderable2D() { }

		virtual void submit(Renderer2D* renderer) const { renderer->submit(this); } //reversing : submiting sprite to renderer but in different query
		
		// getters
		inline const maths::Vec3& getPosition() const { return m_Position; }
		inline const maths::Vec2& getSize() const { return m_Size; }
		inline const maths::Vec4& getColor() const { return m_Color; }
		inline const std::vector<maths::Vec2>& getUV() const { return m_UV; }

		inline const GLuint getTID() const { return m_Texture == nullptr ? 0 : m_Texture->getTextureID(); }
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