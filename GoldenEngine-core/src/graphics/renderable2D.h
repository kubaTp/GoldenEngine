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
		uint32_t color;
	};

	class Renderable2D
	{
	protected:
		Renderable2D() : m_Texture(nullptr) { setDefaultOfUV(); } // set default texture coords
		 
	public:
		Renderable2D(maths::Vec3 position, maths::Vec2 size, uint32_t color) 
			: m_Position(position), m_Size(size), m_Color(color), m_Texture(nullptr)
		{ setDefaultOfUV(); }

		Renderable2D(maths::Vec3 position, maths::Vec2 size, const maths::Vec4& color)
			: m_Position(position), m_Size(size), m_Color(convertColor(color)) 
		{ setDefaultOfUV(); }

		virtual ~Renderable2D() { }

		virtual void submit(Renderer2D* renderer) const { renderer->submit(this); } // reversing : submiting sprite to renderer but in different query
		
		uint32_t convertColor(const maths::Vec4& vec)
		{
			// color is from 0 to 1 in float
			uint8_t r = vec.x * 255.0f;
			uint8_t g = vec.y * 255.0f;
			uint8_t b = vec.z * 255.0f;
			uint8_t a = vec.w * 255.0f;

			uint32_t color = a << 24 | b << 16 | g << 8 | r; // push alfa to the first byte, push b to second byte, push g to third byte, push r to fourth 
			return color;
		}


		// GETTERS
		inline const maths::Vec3& getPosition() const { return m_Position; }
		inline const maths::Vec2& getSize() const { return m_Size; }
		inline const uint32_t& getColor() const { return m_Color; }
		inline const std::vector<maths::Vec2>& getUV() const { return m_UV; }
		inline const GLuint getTID() const { return m_Texture ? m_Texture->getTextureID() : 0; }

		// SETTERS
		void setColor(uint32_t color) { m_Color = color; }
		void setColor(const maths::Vec4& color) { m_Color = convertColor(color); }
		inline void setPosition(const maths::Vec3* newPos) { m_Position = *newPos; }

	protected:
		maths::Vec3 m_Position; // position given
		maths::Vec2 m_Size; // size of renderable
		uint32_t m_Color; // color of renderable
		std::vector<maths::Vec2> m_UV; // texture coords

		Texture* m_Texture; // pointer to texture, because everyone renderable has "own" texture

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