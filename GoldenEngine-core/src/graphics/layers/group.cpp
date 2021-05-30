#include "group.h"

namespace golden { namespace graphics {

	Group::Group(const maths::Mat4& transformationMatrix) : m_TransformationMatrix(transformationMatrix) { }

	Group::~Group()
	{
		for (short i = 0; i < m_Renderables.size(); i++)
			delete m_Renderables[i];
	}

	void Group::submit(Renderer2D* renderer) const
	{
		// push transformation matrix of current group to render on transformation matrix
		renderer->push(m_TransformationMatrix);

		// submit for everyone renderable in renderalbes, group is not rendered but renderables in group yes
		for (const Renderable2D* renderable : m_Renderables)
			renderer->submit(renderable);

		// removing last one matrix (transformation matrix of current group)
		renderer->pop();
	}

	void Group::add(Renderable2D* renderable) { m_Renderables.push_back(renderable); }

	void Group::changeTransformationMatrix(const maths::Mat4& transformationMatrix) { m_TransformationMatrix = transformationMatrix; }
}}