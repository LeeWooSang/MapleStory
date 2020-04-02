#include "CharacterSelectBaseLayer.h"
#include "../../GameObject/Map/Map.h"

CharacterSelectBaseLayer::CharacterSelectBaseLayer()
{
}

CharacterSelectBaseLayer::~CharacterSelectBaseLayer()
{
}

bool CharacterSelectBaseLayer::Initialize()
{
	string name = "CharacterSelectBackground";
	Map* background = new Map(name);
	m_objectList.emplace_back(background);
	if (background->Initialize() == false)
		return false;
	background->SetPosition(VECTOR2D(0.f, 0.f));

	return true;
}

void CharacterSelectBaseLayer::Update(float elapsedTime)
{
	for (auto object : m_objectList)
		object->Update(elapsedTime);
}

void CharacterSelectBaseLayer::Render()
{
	for (auto object : m_objectList)
		object->Render();
}

bool CharacterSelectBaseLayer::CheckCollision(GameObject *, int &)
{
	return false;
}

void CharacterSelectBaseLayer::ProcessCollision(GameObject *, int &)
{
}

void CharacterSelectBaseLayer::ProcessKeyboardMessage(HWND, UINT, WPARAM, LPARAM)
{
}
