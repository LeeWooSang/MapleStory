#include "InGameBaseLayer.h"
#include "../../GameObject/Map/Map.h"
#include "../../GameObject/Character/Player/Player.h"

InGameBaseLayer::InGameBaseLayer()
{
}

InGameBaseLayer::~InGameBaseLayer()
{
}

bool InGameBaseLayer::Initialize()
{
	m_player = new Player("플레이어");
	if (m_player->Initialize() == false)
		return false;

	return true;
}

void InGameBaseLayer::Update(float elapsedTime)
{
	if (m_player != nullptr)
		m_player->Update(elapsedTime);
}

void InGameBaseLayer::Render()
{
	if (m_player != nullptr)
		m_player->Render();
}

bool InGameBaseLayer::CheckCollision(GameObject *, int &)
{
	return false;
}

void InGameBaseLayer::ProcessCollision(GameObject *, int &)
{
}

void InGameBaseLayer::ProcessKeyboardMessage(HWND, UINT, WPARAM, LPARAM)
{
}
