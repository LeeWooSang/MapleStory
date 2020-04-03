#include "Scene.h"
#include "../Layer/Layer.h"
#include "../GameObject/Character/Player/Player.h"

Scene::Scene()
{
	m_layerList.clear();
}

Scene::~Scene()
{
	for (auto iter = m_layerList.begin(); iter != m_layerList.end();)
	{
		delete (*iter).second;
		iter = m_layerList.erase(iter);
	}

	if (m_player != nullptr)
		delete m_player;
}

Layer* Scene::GetLayer(const string& key)
{
	auto iter = m_layerList.find(key);
	if(iter == m_layerList.end())
		return nullptr;

	return (*iter).second;
}
