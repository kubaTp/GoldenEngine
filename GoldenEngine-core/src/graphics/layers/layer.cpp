#include "layer.h"

namespace golden { namespace graphics {

	Layer::Layer(Renderer2D* renderer, Shader& shader, maths::Mat4 projectionMatrix) : m_Renderer(renderer), m_Shader(shader), m_ProjectionMatrix(projectionMatrix)
	{
		m_Shader.enable();
		m_Shader.setUniformMat4("pr_matrix", m_ProjectionMatrix);
		m_Shader.disabled();
	}

	Layer::~Layer() 
	{
		delete m_Renderer;

		for (int i = 0; i < m_RenderablesQueue.size(); i++)
			delete m_RenderablesQueue[i];
	}

	void Layer::add(Renderable2D* renderable)
	{
		m_RenderablesQueue.push_back(renderable);
	}

	void Layer::render()
	{
		m_Shader.enable();
		m_Renderer->begin();

		for (const Renderable2D* renderable : m_RenderablesQueue)
		{
			renderable->submit(m_Renderer);
		}

		m_Renderer->end();
		m_Renderer->flush();
	}
}}