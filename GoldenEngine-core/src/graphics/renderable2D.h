#pragma once

#include <typeinfo>
#include <algorithm>
#include <memory>

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
		inline const maths::Vec2& getSize() const { return m_Size; }
		inline const uint32_t& getColor() const { return m_Color; }
		inline const std::vector<maths::Vec2>& getUV() const { return m_UV; }
		inline const GLuint getTID() const { return m_Texture ? m_Texture->getTextureID() : 0; }
		inline const std::string getTexturePath() const { return m_Texture->getImagePath(); }
	
		template<typename T>
		std::shared_ptr<T> getComponent() const
		{
			std::string targetName = typeid(T).name();		

			for (std::shared_ptr<ecs::Component> comp : m_Components)
			{
				std::string currentName = typeid(*comp).name();

				if (currentName == targetName)
				{
					return std::static_pointer_cast<T>(comp);
				}
			}
		}

		template<typename T>
		bool hasComponent()
		{
			std::string targetName = typeid(T).name();
			for (auto comp : m_Components)
			{
				std::string currentName = typeid(*comp).name();

				if (currentName == targetName)
				{
					return true;
				}
			}

			return false;
		}

		const std::vector<std::shared_ptr<ecs::Component>>& getComponents() const { return m_Components; }

		// SETTERS
		inline void setColor(uint32_t color) { m_Color = color; }
		inline void setColor(const maths::Vec4& color) { m_Color = convertColor(color); }

		template<typename T>
		inline void addComponent()
		{ 
			m_Components.push_back(std::make_shared<T>());
		}

		//inline bool hasComponent
		inline void printSizeOfCompsArray() const { std::cout << "size of comps array is " << m_Components.size() << std::endl; }

	protected:
		// should be part of transform component
		maths::Vec2 m_Size; // size of renderable
		uint32_t m_Color; // color of renderable

		std::vector<maths::Vec2> m_UV; // texture coords
		Texture* m_Texture; // everyone renderable has "own" texture

		std::vector<std::shared_ptr<ecs::Component>> m_Components; // dynamic array of components


		//uint32_t m_RenaderableID;
		//std::string m_Name;
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