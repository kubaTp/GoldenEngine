#include "scene.h"

namespace golden { namespace graphics {

	Scene::Scene() : m_Name("empty scene") { }
	Scene::Scene(std::string name) : m_Name(name) { }

	void Scene::addLayer(std::string name, Layer* layerToBeAdded)
	{
		m_Layers.push_back(std::pair<std::string, graphics::Layer*>(name, layerToBeAdded));
	}

	void Scene::removeLayer(std::string name)
	{
		int32_t index = -1;

		for (uint32_t i = 0; i < m_Layers.size(); i++)
		{
			if (m_Layers[i].first == name)
			{
				index = i;
			}
		}

		if (index >= 0)
			m_Layers.erase(m_Layers.begin() + index);
		else
			Logger::logWarning("You have tried to remove layer that does not exists in the " + m_Name + " scene");		
	}

	void Scene::clearLayers()
	{
		m_Layers.clear();
	}

	void Scene::descLayers() const
	{
		Logger::logInfo("layers");

		for (const auto& layer : m_Layers)
			Logger::logInfo("name of layer : " + layer.first);

		Logger::logSpace();
	}

	inline const std::string& Scene::getName() const { return this->m_Name; }
}}