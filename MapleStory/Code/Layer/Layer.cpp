#include "Layer.h"
#include "../GameObject/GameObject.h"
#include "../GameObject/UI/UI.h"
#include "../Input/Input.h"

Layer::Layer()
{
	m_objectList.clear();
	m_objectMap.clear();
}

Layer::~Layer()
{
	for (auto iter = m_objectList.begin(); iter != m_objectList.end();)
	{
		delete (*iter);
		iter = m_objectList.erase(iter);
	}
	m_objectList.clear();

	for (auto iter = m_objectMap.begin(); iter != m_objectMap.end();)
	{
		delete (*iter).second;
		iter = m_objectMap.erase(iter);
	}
	m_objectMap.clear();
}

bool Layer::CheckCollision(GameObject* object, int& flag)
{
	reinterpret_cast<UI*>(object)->CollideUIAndMouse(flag);

	if (flag & UI::COLLISION_TYPE::NO_COLLISION)
		return false;

	// 마우스 클릭한 경우
	if (GET_INSTANCE(Input)->KeyOnceCheck(KEY_TYPE::MOUSE_LBUTTON) == true)
	{
		flag |= UI::MOUSE_TYPE::CLICK;
		return true;
	}

	else
	{
		flag |= UI::MOUSE_TYPE::NO_CLICLK;
		return false;
	}
}

void Layer::ProcessCollision(GameObject *, int &)
{
}

GameObject* Layer::GetGameObject(int key)
{
	auto iter = m_objectMap.find(key);
	if (iter == m_objectMap.end())
		return nullptr;

	return (*iter).second;
}
