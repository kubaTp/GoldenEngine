#pragma once

#include "../renderers/renderer2D.h"
#include "../renderables/renderable2D.h"
#include ".../../../../base.h"
#include "../../utils/resourceloader.h"

namespace golden { class Chief;  namespace graphics {

	class Layer
	{
	public:
		friend class Chief;
		Layer(Shader& shader, maths::Mat4 projectionMatrix, bool uiLayer = false);

	public:
		virtual ~Layer();

		void add(Renderable2D* renderable);				   // add Renderable2D to the m_RenderablesQueue		
		void changePrMatrix(maths::Mat4 projectionMatrix); // change projection matrix after contructing variables

		inline const std::vector<Renderable2D*>& getRenderables() const { return m_RenderablesQueue; } // get all renderables in the layer
		inline const bool isUILayer() const { return m_UILayer; }

	private:
		void shaderBinding(bool bind) { (bind) ? m_Shader.enable() : m_Shader.disabled(); } // bind or ubind shader from Chief class

	protected:
		std::vector<Renderable2D*> m_RenderablesQueue; // queue of renderables to be rendered
		Shader& m_Shader; // unique shader, taken by refernce
		maths::Mat4 m_ProjectionMatrix; // unique projection matrix of layer
		bool m_UILayer = false;
	};
}}
