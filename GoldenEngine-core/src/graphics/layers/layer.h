#pragma once

#include "../renderer2D.h"
#include "../renderable2D.h"

namespace golden { class Chief;  namespace graphics {

	class Layer
	{
	protected:
		Renderer2D* m_Renderer; // everone layer has own renderer
		std::vector<Renderable2D*> m_RenderablesQueue; // queue of renderables to be rendered
		Shader& m_Shader; // unique shader, taken by refernce
		maths::Mat4 m_ProjectionMatrix; // unique projection matrix of layer

	public:
		friend class Chief;
		Layer(Renderer2D* renderer, Shader& shader, maths::Mat4 projectionMatrix);

	public:
		virtual ~Layer();

		void add(Renderable2D* renderable); // add Renderable2D to the m_RenderablesQueue
		void render(); // bind shader and renderer, submit sprites to renderer, draw them by renderer
		void changePrMatrix(maths::Mat4 projectionMatrix); // change projection matrix after contructing variables

		inline const std::vector<Renderable2D*>& getRenderables() const { return m_RenderablesQueue; } // get all renderables in the layer

	private:
		void shaderBinding(bool bind) { (bind) ? m_Shader.enable() : m_Shader.disabled(); } // bind or ubind shader from Chief class
	};
}}
