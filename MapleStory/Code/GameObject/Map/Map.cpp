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

	StaticObjectInfo* info0 = GET_INSTANCE(ResourceManager)->GetStaticObjectInfo(m_name);
	if (info0 != nullptr)
		SetPosition(VECTOR2D(info0->m_x, info0->m_y));

	AnimatedObjectInfo* info1 = GET_INSTANCE(ResourceManager)->GetAnimatedObjectInfo(m_name);
	if (info1 != nullptr)
	{
		SetPosition(VECTOR2D(info1->m_x, info1->m_y));
		//InitAnimation(info1->m_size, info1->m_animationName);
	}


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