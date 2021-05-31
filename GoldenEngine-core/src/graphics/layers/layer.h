#pragma once

#include "../renderer2D.h"
#include "../renderable2D.h"

namespace golden { namespace graphics {

	class Layer
	{
	protected:
		Renderer2D* m_Renderer; // everone layer has own renderer
		std::vector<Renderable2D*> m_RenderablesQueue; // queue of renderables to be rendered
		Shader& m_Shader; // unique shader
		maths::Mat4 m_ProjectionMatrix; // unique projection matrix of layer

	public:
		Layer(Renderer2D* renderer, Shader& shader, maths::Mat4 projectionMatrix);

	public:
		virtual ~Layer();

		void add(Renderable2D* renderable); // add Renderable2D to the m_RenderablesQueue
		void render(); // bind shader and renderer, submit sprites to renderer, draw them by renderer
		void changePrMatrix(maths::Mat4 projectionMatrix); // change projection matrix after contructing variable
	};
}}
