#include "Map.h"

Map::Map(const string& name)
	: GameObject(name)
{
}

Map::~Map()
{
}

bool Map::Initialize(TextureInfo info)
{
	if (GameObject::Initialize(info) == false)
		return false;

	m_worldMatrix._21 = 0.f;
	m_worldMatrix._22 = -1.f;
	return true;
}

void Map::Update(float elapsedTime)
{
}

void Map::Render()
{	
	GameObject::Render();
}