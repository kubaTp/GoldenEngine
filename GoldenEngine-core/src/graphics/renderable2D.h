#pragma once

#include "buffers/buffer.h"
#include "buffers/indexbuffer.h"
#include "buffers/vertexarray.h"

#include "../maths/maths.h"
#include "shader.h"

#include "renderer2D.h"

#include "texture.h"

#include "../components/components_pack.h"

namespace golden { class Chief; namespace graphics {

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
	private:
		friend class Chief;

	protected:
		Renderable2D(); // default contructor
		 
	public:
		Renderable2D(maths::Vec3 position, maths::Vec2 size, uint32_t color);
		Renderable2D(maths::Vec3 position, maths::Vec2 size, const maths::Vec4& color);
		virtual ~Renderable2D();

		virtual void submit(Renderer2D* renderer) const; // reversing : submiting sprite to renderer but in different query
		
		uint32_t convertColor(const maths::Vec4& vec); // change location of this function

		// GETTERS
		inline const maths::Vec3& getPosition() const { return m_Position; }
		inline const maths::Vec2& getSize() const { return m_Size; }
		inline const uint32_t& getColor() const { return m_Color; }
		inline const std::vector<maths::Vec2>& getUV() const { return m_UV; }
		inline const GLuint getTID() const { return m_Texture ? m_Texture->getTextureID() : 0; }
		ecs::Component* getComponent(std::string name) const;

		// SETTERS
		inline void setColor(uint32_t color) { m_Color = color; }
		inline void setColor(const maths::Vec4& color) { m_Color = convertColor(color); }
		inline void setPosition(const maths::Vec3* newPos) { m_Position = *newPos; }

		inline void printSizeOfCompsArray() const { std::cout << "size of comps array is " << m_Components.size() << std::endl; }

	protected:
		maths::Vec3 m_Position; // position given
		maths::Vec2 m_Size; // size of renderable
		uint32_t m_Color; // color of renderable
		std::vector<maths::Vec2> m_UV; // texture coords

		Texture* m_Texture; // everyone renderable has "own" texture

		std::vector<ecs::Component*> m_Components; // dynamic array of components

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