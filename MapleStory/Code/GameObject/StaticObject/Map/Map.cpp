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
	Texture* tex = GET_INSTANCE(ResourceManager)->GetTexture(m_name);
	if (tex == nullptr)
		return false;

	int width = tex->GetWidth();
	int height = tex->GetHeight();
	m_collider = new AABBCollider(AABB(-width * 0.5f, -height * 0.5f, width * 0.5f, height * 0.5f));

	m_isDrawBoundingBox = true;

	m_worldMatrix._21 = 0.f;
	m_worldMatrix._22 = -1.f;

	StaticObjectInfo* info0 = GET_INSTANCE(ResourceManager)->GetStaticObjectInfo(m_name);
	if (info0 != nullptr)
		SetPosition(VECTOR2D(info0->m_x, info0->m_y));

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