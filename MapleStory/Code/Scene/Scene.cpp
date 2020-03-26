#include "Scene.h"
#include "../GameObject/GameObject.h"

Scene::Scene()
{
	m_objectList.clear();
}

Scene::~Scene()
{
	for (auto iter = m_objectList.begin(); iter != m_objectList.end(); )
	{
		delete (*iter).second;
		iter = m_objectList.erase(iter);
	}
	m_objectList.clear();
}
