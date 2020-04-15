#include "Tile.h"
#include "../../../ResourceManager/ResourceManager.h"
#include "../../../ResourceManager/Texture/Texture.h"

Tile::Tile(const string& name)
	: Map(name)
{
}

Tile::~Tile()
{
}

bool Tile::Initialize()
{
	if (GameObject::Initialize() == false)
		return false;

	m_worldMatrix._21 = 0.f;
	m_worldMatrix._22 = -1.f;

	return true;
}

void Tile::Update(float elapsedTime)
{
}

void Tile::Render()
{
	GameObject::Render();
}

void Tile::GetTopPos()
{
	Texture* tex = GET_INSTANCE(ResourceManager)->GetTexture(m_name);
	
	int halfWidth = tex->GetWidth() * 0.5f;
	int halfHeight = tex->GetHeight() * 0.5f;

	m_topStartPos = VECTOR2D(m_worldMatrix._31 - halfWidth, m_worldMatrix._32 - halfHeight);
	m_topEndPos = VECTOR2D(m_worldMatrix._31 + halfWidth, m_worldMatrix._32 - halfHeight + 5);
}

bool Tile::CheckCollision(GameObject* object)
{
	if (object->GetPositionVector().x < m_topStartPos.x)
		return false;
	if (object->GetPositionVector().x > m_topEndPos.x)
		return false;
	if (object->GetPositionVector().y < m_topStartPos.y)
		return false;
	if (object->GetPositionVector().y > m_topEndPos.y)
		return false;

	return true;
}

