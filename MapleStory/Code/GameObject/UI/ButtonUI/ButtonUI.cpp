#include "ButtonUI.h"

ButtonUI::ButtonUI(const string& name)
	: UI(name)
{
}

ButtonUI::~ButtonUI()
{
}

bool ButtonUI::Initialize()
{
	GameObject::Initialize();

	m_worldMatrix._21 = 0.f;
	m_worldMatrix._22 = -1.f;

	return true;
}

void ButtonUI::Update(float elapsedTime)
{
}

void ButtonUI::Render()
{
	GameObject::Render();
}
