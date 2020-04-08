#include "InGameBaseLayer.h"
#include "../../GameObject/Map/Map.h"
#include "../../GameObject/Character/Player/Player.h"

InGameBaseLayer::InGameBaseLayer()
{
}

InGameBaseLayer::~InGameBaseLayer()
{
	if (m_player != nullptr)
		delete m_player;
}

bool InGameBaseLayer::Initialize()
{
	//Map* henesysBackground5 = new Map("HenesysBackground5");
	//m_objectList.emplace_back(henesysBackground5);
	//if (henesysBackground5->Initialize() == false)
	//	return false;
	//henesysBackground5->InitWrap();
	//henesysBackground5->SetPosition(VECTOR2D(-25.f, -60.f));

	//Map* henesysBackground6 = new Map("HenesysBackground6");
	//m_objectList.emplace_back(henesysBackground6);
	//if (henesysBackground6->Initialize() == false)
	//	return false;
	//henesysBackground6->InitWrap();
	//henesysBackground6->SetPosition(VECTOR2D(0.f, 0.f));

	for (int i = 0; i < 6; ++i)
	{
		string name = "WoodMarbleTile" + to_string(i);

		Map* tile = new Map(name);
		m_objectList.emplace_back(tile);
		if (tile->Initialize() == false)
			return false;
		//tile->InitWrap();
		tile->SetPosition(VECTOR2D(90.f * i, 10.f));
	}

	m_player = new Player("플레이어");
	if (m_player->Initialize() == false)
		return false;

	return true;
}

void InGameBaseLayer::Update(float elapsedTime)
{
	for (auto object : m_objectList)
		object->Update(elapsedTime);

	if (m_player != nullptr)
		m_player->Update(elapsedTime);
}

void InGameBaseLayer::Render()
{
	for (auto object : m_objectList)
		object->Render();

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
