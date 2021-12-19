#include "chief.h"

golden::graphics::Renderer2D* golden::Chief::m_Renderer2D;

std::map<std::string, golden::graphics::Layer*> golden::Chief::m_Layers;
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

	void Chief::addLayer(std::string name, graphics::Layer* layer)
	{
		m_Layers.insert(std::pair<std::string, graphics::Layer*>(name, layer));
	}
	void Chief::removeLayer(std::string name)
	{
		m_Layers.erase(m_Layers.find(name));
	}
	void Chief::clearLayers()
	{
		m_Layers.clear();
	}

	void Chief::render()
	{
		if (m_Inited)
		{
			for (auto const& layer : m_Layers)
				render_layer(layer.second);
		}
		else
			Logger::logError("Could not renderer layers because chief has not been inited yet!");

		m_FirstFrame = false;
	}
	void Chief::descLayers()
	{
		Logger::logInfo("added layers: ");
		for (auto const& layer : m_Layers)
			Logger::logInfo("name of layer : " + layer.first);
		
		Logger::logSpace();
	}

	void Chief::render(std::string name) // TODO : change name
	{
		render_layer(m_Layers.find(name)->second);

		m_FirstFrame = false;
	}

	void Chief::render_layer(graphics::Layer* layer)
	{
		//framebuffer->Bind();
		
		layer->shaderBinding(true);
		m_Renderer2D->begin();

		for (const graphics::Renderable2D* renderable : layer->getRenderables())
		{			
			if (m_FirstFrame)
			{
				renderable->getComponent("BehaviourComponent")->InvokeOnStartFunction();
			}
			else
			{
				renderable->getComponent("BehaviourComponent")->InvokeOnUpdateFunction();
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