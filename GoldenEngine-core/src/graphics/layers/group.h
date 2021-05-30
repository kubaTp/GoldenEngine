#pragma once

#include "../renderable2D.h"

namespace golden { namespace graphics {

	class Group : public Renderable2D
	{
	private:
		std::vector<Renderable2D*> m_Renderables;
		maths::Mat4 m_TransformationMatrix; // transformation matrix used in all sprites, used as a reference position to child sprites

	public:
		Group(const maths::Mat4& transformationMatrix);
		~Group();

		void submit(Renderer2D* renderer) const override; // push m_TransformationMatrix to transformation stack in renderer, submit sprites to specyfic renderer, delete given m_TransformationMatrix from transformation stack in renderer
		void add(Renderable2D* renderable); // add a renderable to m_Renderables
		void changeTransformationMatrix(const maths::Mat4& transformationMatrix); // change transformation matrix after conctruciting object
	};
}}