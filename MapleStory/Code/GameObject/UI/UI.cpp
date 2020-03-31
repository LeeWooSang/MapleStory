#include "UI.h"
#include "../../Camera/Camera.h"
#include "../../Input/Input.h"
#include "../../ResourceManager/ResourceManager.h"
#include "../../ResourceManager/Texture/Texture.h"

UI::UI(const string& name)
	: GameObject(name)
{
}

UI::~UI()
{
}

bool UI::Initialize()
{
	return true;
}

void UI::Update(float elapsedTime)
{
}

void UI::Render()
{
}

void UI::CollideUIAndMouse(int& flag)
{
	Matrix3x2F worldView = m_worldMatrix * GET_INSTANCE(Camera)->GetViewMatrix();
	VECTOR2D pos = VECTOR2D(worldView._31, worldView._32);

	Texture* tex = GET_INSTANCE(ResourceManager)->GetTexture(m_name);

	int minX = pos.x - tex->GetWidth() * 0.5f;
	int minY = pos.y - tex->GetHeight() * 0.5f;
	int maxX = minX + tex->GetWidth();
	int maxY = minY + tex->GetHeight();

	POINT mousePos = GET_INSTANCE(Input)->GetMousePos();

	// 충돌 안한 경우
	if (minX > mousePos.x)
	{
		flag |= COLLISION_TYPE::NO_COLLISION;
	}

	else if (maxX < mousePos.x)
	{
		flag |= COLLISION_TYPE::NO_COLLISION;
	}

	else if (minY > mousePos.y)
	{
		flag |= COLLISION_TYPE::NO_COLLISION;
	}

	else if (maxY < mousePos.y)
	{
		flag |= COLLISION_TYPE::NO_COLLISION;
	}

	else
		flag |= COLLISION_TYPE::COLLISION;
}
