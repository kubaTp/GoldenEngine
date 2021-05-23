#pragma once

#include "../renderable2D.h"

namespace golden { namespace graphics {

	class Group : Renderable2D
	{
	private:
		std::vector<Renderable2D*> m_Renderables;
		maths::Mat4 m_TransformationMatrix;

	public:
		Group();
		void submit(Renderer2D* renderer) const override;
	};
}}