#include "Tile.h"
#include "../../../ResourceManager/Texture/Texture.h"

Tile::Tile(const string& name)
	: StaticObject(name)
{
}

Tile::~Tile()
{
}

bool Tile::Initialize(const string& textureName)
{
	if (StaticObject::Initialize(textureName) == false)
		return false;

	return true;
}

void Tile::Update(float elapsedTime)
{
	StaticObject::Update(elapsedTime);
}

void Tile::Render()
{
	StaticObject::Render();
}

void Tile::GetTopPos()
{
	auto iter = m_textureMap.find(m_textureName);
	if (iter == m_textureMap.end())
		return;

	int halfWidth = (*iter).second->GetWidth() * 0.5f;
	int halfHeight = (*iter).second->GetHeight() * 0.5f;

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

