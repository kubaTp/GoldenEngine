#pragma once

//#include <map>
#include <unordered_map>
#include <iostream>

#include "../../base.h"
#include "../../utils/logger.h"
#include "../layers/layers_pack.h"
#include "../camera.h"

// 2D SCENE
namespace golden { class Chief; namespace graphics {

	class Scene
	{
	public:
		Scene();
		Scene(std::string name);

		inline void setName(std::string name) { m_Name = name; }
		inline const std::string& getName() const;

		void addLayer(std::string name, graphics::Layer* layer); // add layer to map, string is key for layer
		void removeLayer(std::string name);						 // remove layer from the array
		void clearLayers();										 // clear all layers in the array
		void descLayers() const;								 // print all layers in the array
		void insertCamera(Camera* cam);						     // insert main camera

		std::vector<std::pair<std::string, Layer*>>& getLayers() { return this->m_Layers; }
		inline const std::string& getName()						 { return m_Name;		  }
		Camera* getCamera() const								 { return m_MainCamera;   }

		friend class Chief;

	private:
		std::string m_Name;						              // name of scene
		std::vector<std::pair<std::string, Layer*>> m_Layers; // vector of layers
		Camera* m_MainCamera;								  // main camera
	};
}}