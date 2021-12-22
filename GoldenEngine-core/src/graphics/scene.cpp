#include "scene.h"

namespace golden { namespace graphics {

	Scene::Scene() : m_Name("empty scene") { }
	Scene::Scene(std::string name) : m_Name(name) { }

	void Scene::addLayer(std::string name, Layer* layerToBeAdded)
	{
		m_Layers.insert(std::pair<std::string, graphics::Layer*>(name, layerToBeAdded));
	}

	void Scene::removeLayer(std::string name)
	{
		m_Layers.erase(m_Layers.find(name));
	}
	void Scene::clearLayers()
	{
		m_Layers.clear();
	}
	void Scene::descLayers() const
	{
		Logger::logInfo("added layers: ");
		for (auto const& layer : m_Layers)
			Logger::logInfo("name of layer : " + layer.first);

		Logger::logSpace();
	}

	inline const std::string& Scene::getName() const { return this->m_Name; }
}}