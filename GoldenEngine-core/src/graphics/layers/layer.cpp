#include "layer.h"

namespace golden { namespace graphics {

	Layer::Layer(Shader& shader, maths::Mat4 projectionMatrix, bool uiLayer) :  m_Shader(shader), m_ProjectionMatrix(projectionMatrix), m_UILayer(uiLayer)
	{
		//set specified matrix to projection matrix in specified shader
		m_Shader.enable();
		m_Shader.setUniformMat4("pr_matrix", m_ProjectionMatrix);
		m_Shader.disabled();
	}

	Layer::~Layer() 
	{
		for (int i = 0; i < m_RenderablesQueue.size(); i++)
			delete m_RenderablesQueue[i];
	}

	void Layer::add(Renderable2D* renderable)
	{
		m_RenderablesQueue.push_back(renderable);
	}

	void Layer::changePrMatrix(maths::Mat4 projectionMatrix)
	{
		m_ProjectionMatrix = projectionMatrix;

		m_Shader.enable();
		m_Shader.setUniformMat4("pr_matrix", m_ProjectionMatrix);
		m_Shader.disabled();
	}
}}