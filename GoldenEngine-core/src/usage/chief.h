#pragma once

#include <unordered_map>
#include <string>
#include <iostream>

#include "../utils/logger.h"
#include "../graphics/renderer2D.h"
#include "../graphics/batchrenderer2D.h"
#include "../graphics/layers/layer.h"
#include "../graphics/buffers/framebuffer.h"

#include "../graphics/scene.h"

namespace golden {

	class Chief
	{
	private:
		Chief();

	public:
		static void init(graphics::Renderer2D* renderer); // init Chief with renderer, now just works with Batchrenderer
		static graphics::Renderer2D* getRenderer(); // returns pointer to renderer
		
		static void addLayer(std::string name, graphics::Layer* layer); // add layer to map, string is key for layer
		static void removeLayer(std::string name); // remove layer from the array
		static void clearLayers(); // clear all layers in the array
		static void descLayers(); // print all layers in the array

		static void render(); // render all layers in the array
		static void render(std::string name); // render just one layer by given key

		static bool firstFrame() { return m_FirstFrame; }

		static void insertScene(graphics::Scene* scene) 
		{ 
			m_ActiveScene = scene;
		}
		
		static void drawScene() // draw all scenes in the scene submited to chief
		{
			render();
		}

		static void drawScene(std::string layername) // draw only one layer from layers submited in the scene
		{
			render(layername);
		}

	private:
		static void render_layer(graphics::Layer* layer); // private render method for one layer

	public:
		static graphics::Framebuffer* framebuffer;

	private:
		static graphics::Renderer2D* m_Renderer2D;
		static bool m_Inited;
		static bool m_FirstFrame;

		static golden::graphics::Scene* m_ActiveScene; // current scene
		//static std::vector<std::pair<std::string, golden::graphics::Layer*>> m_Layers;

		static graphics::FramebufferSpecification spec;
	};
}