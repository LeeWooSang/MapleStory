#include "InGameBaseLayer.h"
#include "../../GameObject/Map/Map.h"
#include "../../GameObject/Character/Player/Player.h"
#include "../../../../GameServer/Code/Protocol.h"
#include "../../Camera/Camera.h"

InGameBaseLayer::InGameBaseLayer()
{
}

InGameBaseLayer::~InGameBaseLayer()
{
	if (m_player != nullptr)
		delete m_player;

	SAFE_DELETE_LIST(m_tileTopList);
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

	int tileNum = 0;
	float startX = -WORLD_WIDTH * 0.5f;
	float startY = WORLD_HEIGHT * 0.5f;
	int gapX = 90;
	int gapY = -60;

	// WoodMarbleTile
	// 가로
	for (int i = 0; i < 67; ++i)
	{
		// 세로
		for (int j = 0; j < 4; ++j)
		{
			if (tileNum >= 6)
				tileNum = 0;

			string name = "WoodMarbleTile" + to_string(tileNum++);

			Map* tile = new Map(name);
			m_tileTopList.emplace_back(tile);
			if (tile->Initialize() == false)
				return false;
			tile->SetPosition(VECTOR2D(startX + gapX * i, startY + gapY * j));
		}
	}

	// WoodMarbleTop
	for (int i = 0; i < 67; ++i)
	{
		if (tileNum >= 4)
			tileNum = 0;

		string name = "WoodMarbleTop" + to_string(tileNum++);

		Map* tile = new Map(name);
		m_objectList.emplace_back(tile);
		if (tile->Initialize() == false)
			return false;
		tile->SetPosition(VECTOR2D(startX + gapX * i, startY - 180 - 30 - 33*0.5));
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

	for (auto tile : m_tileTopList)
		tile->Update(elapsedTime);

	if (m_player != nullptr)
		m_player->Update(elapsedTime);
}

void InGameBaseLayer::Render()
{
	for (auto object : m_objectList)
		if(GET_INSTANCE(Camera)->IsVisible(object) == true)
			object->Render();

	for (auto tile : m_tileTopList)
		if (GET_INSTANCE(Camera)->IsVisible(tile) == true)
			tile->Render();

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
