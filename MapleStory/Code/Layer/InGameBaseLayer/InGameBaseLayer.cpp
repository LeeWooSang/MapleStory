#include "InGameBaseLayer.h"
#include "../../GameObject/Map/Map.h"
#include "../../GameObject/AnimatedObject/AnimatedObject.h"
#include "../../GameObject/Map/Tile/Tile.h"

#include "../../GameObject/Character/Player/Player.h"
#include "../../../../GameServer/Code/Protocol.h"
#include "../../Camera/Camera.h"

#include "../../ResourceManager/ResourceManager.h"

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

	AnimatedObject* flag = new AnimatedObject("HenesysHouse1_Flag");
	m_objectList.emplace_back(flag);
	if (flag->Initialize() == false)
		return false;
	AnimatedObjectInfo* info = GET_INSTANCE(ResourceManager)->GetAnimatedObjectInfo("HenesysHouse1_Flag");
	flag->SetPosition(VECTOR2D(info->m_x, info->m_y));
	flag->InitAnimation(info->m_size, info->m_animationName, info->m_name);
	flag->SetAnimation(info->m_animationName);

	for (int i = 0; i < 8; ++i)
	{
		string name = "HenesysHouse" + to_string(i);
		Map* house = new Map(name);
		m_objectList.emplace_back(house);
		if (house->Initialize() == false)
			return false;
	}



	int tileNum = 0;
	float startX = -WORLD_WIDTH * 0.5f;
	float startY = WORLD_HEIGHT * 0.5f;
	int gapX = 90;
	int gapY = -60;

	// WoodMarbleTile
	// ����
	for (int i = 0; i < 67; ++i)
	{
		// ����
		for (int j = 0; j < 4; ++j)
		{
			if (tileNum >= 6)
				tileNum = 0;

			string name = "WoodMarbleTile" + to_string(tileNum++);

			Map* tile = new Map(name);
			m_objectList.emplace_back(tile);
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

		Tile* tile = new Tile(name);
		m_tileTopList.emplace_back(tile);
		if (tile->Initialize() == false)
			return false;
		tile->SetPosition(VECTOR2D(startX + gapX * i, startY - 180 - 30 - 33*0.5));
		tile->GetTopPos();
	}

	m_player = new Player("�÷��̾�");
	if (m_player->Initialize() == false)
		return false;

	return true;
}

void InGameBaseLayer::Update(float elapsedTime)
{
	int flag = 0;
	for (auto tile : m_tileTopList)
	{
		if (CheckCollision(tile, flag) == true)
		{
			m_player->SetCollisionObject(tile);
			break;
		}
	}	
	if (flag == 0)
		m_player->SetCollisionObject(nullptr);


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

bool InGameBaseLayer::CheckCollision(GameObject* tile, int& flag)
{
	if (m_player == nullptr)
		return false;

	GameObject* object = m_player->FindObject("Body");
	if (object == nullptr)
		return false;

	if (object->GetCollider() == nullptr)
		return false;

	if (reinterpret_cast<Tile*>(tile)->CheckCollision(object) == true)
	{
		flag = 1;
		return true;
	}

	return false;
}

void InGameBaseLayer::ProcessCollision(GameObject *, int &)
{
}

void InGameBaseLayer::ProcessKeyboardMessage(HWND, UINT, WPARAM, LPARAM)
{
}
