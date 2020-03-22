#include "Scene.h"
#include "../Network/Network.h"
#include "../GameObject/GameObject.h"

Scene::~Scene()
{
}

GameObject* Scene::FindObject(int id) const 
{
	for (auto iter = m_ObjectList.begin(); iter != m_ObjectList.end(); ++iter)
	{
		if ((*iter)->GetID() == id)
			return (*iter);
	}

	return nullptr;
}
