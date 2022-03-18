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

#include "renderables2d_idService.h"

namespace golden { class Chief; namespace graphics {

	struct VertexData		// struct represents one of 4 vertex in one sprite
	{
		maths::Vec3 vertex; // vertecies
		maths::Vec2 uv;		// texture coords
		float tid;		    // texture id
		uint32_t color;     // maths::Vec4 color;
	};

	class Renderable2D
	{
	private:
		friend class Chief;

	protected:
		Renderable2D();

	public:
		Renderable2D(maths::Vec3 position, maths::Vec2 size, uint32_t color);
		Renderable2D(maths::Vec3 position, maths::Vec2 size, const maths::Vec4& color);
		Renderable2D(std::string name, maths::Vec3 position, maths::Vec2 size, uint32_t color);
		Renderable2D(std::string name, maths::Vec3 position, maths::Vec2 size, const maths::Vec4& color);

		virtual ~Renderable2D();

		virtual void submit(Renderer2D* renderer) const; // reversing : submiting sprite to renderer but in different query
		uint32_t convertColor(const maths::Vec4& vec);   // change place of this functions

		#pragma region ECS_FUNCTIONS

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
		template<typename T>
		void addComponent()
		{
			GE_ASSERT(hasComponent<T>(), "Could not add component because it has been already added");
			m_Components.push_back(std::make_shared<T>());
		}
		const std::vector<std::shared_ptr<ecs::Component>>& getComponents() const { return m_Components; }
		#pragma endregion

		inline const uint32_t& getColor() const				 { return m_Color;									       }
		inline const std::vector<maths::Vec2>& getUV() const { return m_UV;										       }
		inline const GLuint getTID() const					 { return m_Texture ? m_Texture->getTextureID() : 0;	   }
		inline const std::string getTexturePath() const		 { return m_Texture ? m_Texture->getImagePath() : "empty"; }
		inline const uint32_t getRenderable2dID() const      { return m_RenderableID;						           }
		inline const std::string getName() const			 { return m_Name;									       }

		inline void setColor(uint32_t color)				 { m_Color = color;									       }
		inline void setColor(const maths::Vec4& color)		 { m_Color = convertColor(color);					       }

		inline void printSizeOfCompsArray() const { std::cout << "size of comps array is " << m_Components.size() << std::endl; }

	protected:
		// add width and height
		std::string m_Name = "unnamed";								// name of renderable
		uint32_t m_Color;											// color of renderable

		std::vector<maths::Vec2> m_UV;								// texture coords
		Texture* m_Texture;											// everyone renderable has "own" texture

		std::vector<std::shared_ptr<ecs::Component>> m_Components;  // array of components

		uint64_t m_RenderableID;		     					    // unique if for each renderable in game

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