#include "CharacterSelectBaseLayer.h"
#include "../../GameObject/StaticObject/StaticObject.h"

CharacterSelectBaseLayer::CharacterSelectBaseLayer()
{
}

CharacterSelectBaseLayer::~CharacterSelectBaseLayer()
{
}

bool CharacterSelectBaseLayer::Initialize()
{
	string name = "CharacterSelectBackground";
	StaticObject* background = new StaticObject(name);
	m_objectList.emplace_back(background);
	if (background->Initialize() == false)
		return false;
	background->SetPosition(VECTOR2D(0.f, 0.f));

	name = "Frame";
	StaticObject* frame = new StaticObject(name);
	m_objectList.emplace_back(frame);
	if (frame->Initialize() == false)
		return false;
	frame->SetPosition(VECTOR2D(0.f, 0.f));

	name = "CharacterSelectLogo";
	StaticObject* characterSelectLogo = new StaticObject(name);
	m_objectList.emplace_back(characterSelectLogo);
	if (characterSelectLogo->Initialize() == false)
		return false;
	characterSelectLogo->SetPosition(VECTOR2D(-300.f, -279.f));

	name = "WorldLogoBackground";
	StaticObject* worldLogoBackground = new StaticObject(name);
	m_objectList.emplace_back(worldLogoBackground);
	if (worldLogoBackground->Initialize() == false)
		return false;
	worldLogoBackground->SetPosition(VECTOR2D(272.5f, -222.5f));

	name = "WorldLogoIcon";
	StaticObject* worldLogoIcon = new StaticObject(name);
	m_objectList.emplace_back(worldLogoIcon);
	if (worldLogoIcon->Initialize() == false)
		return false;
	worldLogoIcon->SetPosition(VECTOR2D(225.f, -222.5f));

	name = "WorldLogoName";
	StaticObject* worldLogoName = new StaticObject(name);
	m_objectList.emplace_back(worldLogoName);
	if (worldLogoName->Initialize() == false)
		return false;
	worldLogoName->SetPosition(VECTOR2D(295.f, -230.5f));

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
