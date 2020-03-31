#include "NoticeUI.h"

NoticeUI::NoticeUI(const string& name)
	: UI(name)
{
	m_isActive = false;
}

NoticeUI::~NoticeUI()
{
}

bool NoticeUI::Initialize()
{
	if (GameObject::Initialize() == false)
		return false;

	m_worldMatrix._21 = 0.f;
	m_worldMatrix._22 = -1.f;

	m_isActive = true;

	m_isDrawBoundingBox = false;

	return true;
}

void NoticeUI::Update(float elapsedTime)
{
}

void NoticeUI::Render()
{
	if (m_isActive == true)
		GameObject::Render();
}
