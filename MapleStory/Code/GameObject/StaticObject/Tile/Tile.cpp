#include "Tile.h"
#include "../../../ResourceManager/Texture/Texture.h"
#include "../../AnimatedObject/AnimatedObject.h"

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

void Tile::SetTopPos()
{
	auto iter = m_textureMap.find(m_textureName);
	if (iter == m_textureMap.end())
		return;

	int halfWidth = (*iter).second->GetWidth() * 0.5f;
	int halfHeight = (*iter).second->GetHeight() * 0.5f;

	m_topStartPos = VECTOR2D(m_worldMatrix._31 - halfWidth, m_worldMatrix._32 - halfHeight);
	m_topEndPos = VECTOR2D(m_worldMatrix._31 + halfWidth, m_worldMatrix._32 - halfHeight + 1);
}

bool Tile::CheckCollision(AnimatedObject* object)
{
	AnimatedObject* obj = reinterpret_cast<AnimatedObject*>(object);

	if (obj->GetPositionVector().x < m_topStartPos.x)
		return false;
	if (obj->GetPositionVector().x > m_topEndPos.x)
		return false;
	if (obj->GetObjectBottomPos() < m_topStartPos.y)
		return false;
	if (obj->GetObjectBottomPos() > m_topEndPos.y)
		return false;

	return true;
}

