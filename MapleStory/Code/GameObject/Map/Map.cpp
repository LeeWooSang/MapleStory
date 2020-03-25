#include "Map.h"
#include "../../Camera/Camera.h"

Map::Map(const string& name)
	: GameObject(name)
{
}

Map::~Map()
{
}

bool Map::Initialize(TextureInfo info)
{
	if (GET_INSTANCE(D2DManager)->CreateTexture(m_name, info) == false)
		return false;

	return true;
}

void Map::Update(float elapsedTime)
{
}

void Map::Render()
{	
	TextureInfo info = GET_INSTANCE(D2DManager)->GetTexture(m_name);

	Matrix3x2F transform = m_worldMatrix;

	transform = transform * GET_INSTANCE(Camera)->GetViewMatrix();
	GET_INSTANCE(D2DManager)->GetRenderTarget()->SetTransform(transform);

	D2D1_RECT_F rect;
	m_collider->GetAABB(&rect);
	GET_INSTANCE(D2DManager)->GetRenderTarget()->DrawBitmap(info.m_image, rect);
}