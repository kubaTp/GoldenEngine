#pragma once

#include <map>
#include <string>
#include <iostream>

#include "logger.h"
#include "../graphics/renderer2D.h"
#include "../graphics/batchrenderer2D.h"
#include "../graphics/layers/layer.h"

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

		static void renderer(); // renderer all layers in the array
		static void renderer(std::string name); // render just one layer by given key

	private:
		static void render_layer(graphics::Layer* layer); // private render method for one layer

	private:
		static graphics::Renderer2D* m_Renderer2D;
		static bool m_Inited;

		static std::map<std::string, graphics::Layer*> m_Layers;
	};
}