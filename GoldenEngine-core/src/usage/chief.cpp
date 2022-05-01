#include "chief.h"

golden::graphics::Renderer2D* golden::Chief::m_Renderer2D;

golden::graphics::Scene* golden::Chief::m_ActiveScene;
bool golden::Chief::m_Inited = false;

golden::graphics::Framebuffer* golden::Chief::framebuffer;
golden::graphics::FramebufferSpecification golden::Chief::spec;
bool golden::Chief::m_FirstFrame;

namespace golden {

	void Chief::init(graphics::Renderer2D* renderer) 
	{ 
		m_Inited = true; 
		m_Renderer2D = renderer;

		//framebuffer spec
		spec.Width = 960.0f;
		spec.Height = 540.0f;

		framebuffer = new graphics::Framebuffer(spec);

		m_FirstFrame = true;
	}

	graphics::Renderer2D* Chief::getRenderer() { return m_Renderer2D; }

	void Chief::render()
	{
		if (m_Inited)
		{
			std::for_each(m_ActiveScene->getLayers().begin(), m_ActiveScene->getLayers().end(),
				[](std::pair<std::string, golden::graphics::Layer*> layer)
				{					
					render_layer(layer.second);
				});
		}
		else
			Logger::logError("Could not renderer layers because chief has not been inited yet!");

		m_FirstFrame = false;
	}
	void Chief::descLayers()
	{
		Logger::logInfo("added layers: ");
		for (const auto& layer : m_ActiveScene->getLayers())
			Logger::logInfo("name of layer : " + layer.first);
		
		Logger::logSpace();
	}

	void Chief::render(std::string NameOfLayer) // TODO : render only one layer
	{
		for (const auto& layer : m_ActiveScene->getLayers())
		{
			if (layer.first == NameOfLayer)
			{
				render_layer(layer.second);
			}
		}

		m_FirstFrame = false;
	}

	void Chief::render_layer(graphics::Layer* layer)
	{
		//framebuffer->Bind();

		layer->shaderBinding(true);
		m_Renderer2D->begin();
		
		if(!layer->isUILayer())
			layer->m_Shader.setUniformMat4("vw_matrix", m_ActiveScene->m_MainCamera->cameraMatrix()); // apply camera matrix | todo : check if matrix need to be updated

		for (graphics::Renderable2D* renderable : layer->getRenderables())
		{		
			if (renderable->hasComponent<ecs::TransformComponent>())
			{
				//std::shared_ptr<ecs::TransformComponent> transformComp = renderable->getComponent<ecs::TransformComponent>();
				//layer->m_Shader.setUniformMat4("ml_matrix", maths::Mat4::rotation(transformComp->rotation.x, 
					//maths::Vec3(1, 0, 0)) * maths::Mat4::rotation(transformComp->rotation.y, maths::Vec3(0, 1, 0)) * maths::Mat4::rotation(transformComp->rotation.z, maths::Vec3(0, 0, 1)));
			}

			if (m_FirstFrame)
			{
				for (std::shared_ptr<ecs::Component> comp : renderable->getComponents())
				{
					//std::string targetName = typeid(comp).name();
					comp->InvokeOnStartFunction();
				}
			}
			else
			{
				for (std::shared_ptr<ecs::Component> comp : renderable->getComponents())
				{
					comp->InvokeOnUpdateFunction();
				}
			}

			renderable->submit(m_Renderer2D);
		}

		m_Renderer2D->end();	
		m_Renderer2D->flush();
		layer->shaderBinding(false);

		m_Renderer2D->reset(); // reset all data from one layer

		//framebuffer->Unbind();		
	}
}