#include "simple2Drenderer.h"

namespace golden { namespace graphics {

	//submit renderable to be rendered
	void Simple2DRenderer::submit(const Renderable2D* renderable)
	{
		m_RenderQueue.push_back((StaticSprite*)renderable);
	}

	void Simple2DRenderer::flush()
	{
		const StaticSprite* s_sprite;

		while (!m_RenderQueue.empty())
		{
			s_sprite = m_RenderQueue.front();

			s_sprite->getVAO()->bind();
			s_sprite->getIBO()->bind();
		
			//s_sprite->getShader().setUniformMat4("ml_matrix", maths::Mat4::translation(s_sprite->getPosition()));

			glDrawElements(GL_TRIANGLES, s_sprite->getIBO()->getCount(), GL_UNSIGNED_SHORT, nullptr);
		
			s_sprite->getIBO()->unbind();
			s_sprite->getVAO()->unbind();

			m_RenderQueue.pop_front();
		}
	}
}}