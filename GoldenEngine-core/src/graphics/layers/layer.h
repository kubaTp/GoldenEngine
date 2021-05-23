#pragma once

#include "../renderer2D.h"
#include "../renderable2D.h"

namespace golden { namespace graphics {

	class Layer
	{
	protected:
		Renderer2D* m_Renderer;
		std::vector<Renderable2D*> m_RenderablesQueue;
		Shader& m_Shader;
		maths::Mat4 m_ProjectionMatrix;

	public:
		Layer(Renderer2D* renderer, Shader& shader, maths::Mat4 projectionMatrix);

	public:
		virtual ~Layer();

		void add(Renderable2D* renderable);
		void render();
	};
}}
