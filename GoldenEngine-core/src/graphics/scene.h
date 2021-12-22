#pragma once

#include <map>
#include <iostream>

#include "../base.h"
#include "../utils/logger.h"
#include "layers/layers_pack.h"


// right now just 2d scene
namespace golden { class Chief; namespace graphics {

	struct SceneSpec {
		std::string name;
		std::map<std::string, Layer*> layers;

		friend std::ostream& operator<<(std::ostream& os, const SceneSpec& ss)
		{
			os << "Scene Spec " << "name : " << ss.name << " layers count : " << ss.layers.size() << std::endl;
			return os;
		}

		SceneSpec() : name("empty") { }
	};

	class Scene
	{
	public:
		Scene();
		Scene(std::string name);

		inline void setName(std::string name) { m_Name = name; }
		inline const std::string& getName() const;

		void addLayer(std::string name, graphics::Layer* layer); // add layer to map, string is key for layer
		void removeLayer(std::string name); // remove layer from the array
		void clearLayers(); // clear all layers in the array
		void descLayers() const; // print all layers in the array

		const SceneSpec& sceneSpec() const // convert Scene to SceneSpec struct
		{
			SceneSpec* scenespec = new SceneSpec();
			
			scenespec->name = this->m_Name;
			scenespec->layers = this->m_Layers;

			return *scenespec;
		}

	private:
		std::map<std::string, graphics::Layer*> getLayers() { return this->m_Layers; }
		friend class Chief;

	private:
		std::string m_Name;
		std::map<std::string, Layer*> m_Layers;
	};
}}