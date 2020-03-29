#include "LoginUI.h"
#include "../../../Input/Input.h"
#include "../../../Camera/Camera.h"

LoginUI::LoginUI(const string& name)
	: UI(name)
{
}

LoginUI::~LoginUI()
{
}

bool LoginUI::Initialize()
{
	if (GameObject::Initialize() == false)
		return false;

	m_worldMatrix._21 = 0.f;
	m_worldMatrix._22 = -1.f;

	return true;
}

void LoginUI::Update(float elapsedTime)
{
}

void LoginUI::Render()
{
	GameObject::Render();
}
void LoginUI::Input()
{

}
