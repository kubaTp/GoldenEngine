#include "group.h"

namespace golden { namespace graphics {

	Group::Group() {}

	void Group::submit(Renderer2D* renderer) const
	{
		renderer->push(m_TransformationMatrix);

		for (const Renderable2D* renderable : m_Renderables)
			renderable->submit(renderer);
	}

}}