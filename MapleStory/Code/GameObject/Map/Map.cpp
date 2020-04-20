#include "Map.h"
#include "../../ResourceManager/ResourceManager.h"
#include "../../ResourceManager/Texture/Texture.h"

Map::Map(const string& name)
	: GameObject(name)
{
}

Map::~Map()
{
}

bool Map::Initialize()
{
	if (GameObject::Initialize() == false)
		return false;

	m_worldMatrix._21 = 0.f;
	m_worldMatrix._22 = -1.f;

	ObjectInfo* info = GET_INSTANCE(ResourceManager)->GetObjectInfo(m_name);
	if (info != nullptr)
		SetPosition(VECTOR2D(info->m_x, info->m_y));

	return true;
}

void Map::Update(float elapsedTime)
{
}

void Map::Render()
{	
	GameObject::Render();
}

void Map::InitWrap()
{
	Texture* tex = GET_INSTANCE(ResourceManager)->GetTexture(m_name);
	tex->InitWrap();
}