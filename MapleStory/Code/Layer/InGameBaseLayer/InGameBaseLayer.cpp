#include "InGameBaseLayer.h"
#include "../../GameObject/AnimatedObject/AnimatedObject.h"
#include "../../GameObject/StaticObject/StaticObject.h"

#include "../../GameObject/StaticObject/Tile/Tile.h"

#include "../../GameObject/AnimatedObject/Character/Player/Player.h"
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

	{
		AnimatedObjectInfo* info = GET_INSTANCE(ResourceManager)->GetAnimatedObjectInfo("HenesysHouse1_Flag");
		AnimatedObject* flag = new AnimatedObject(info->m_objectName);
		m_objectList.emplace_back(flag);
		if (flag->Initialize() == false)
			return false;
		flag->SetPosition(VECTOR2D(info->m_x, info->m_y));
		flag->InitAnimation(info->m_size, info->m_animationName, info->m_textureName);
		flag->SetAnimation(info->m_animationName);
	}

	{
		unordered_multimap<string, StaticObjectInfo*> staticObjectInfoList = GET_INSTANCE(ResourceManager)->GetStaticObjectInfoList();
		for (auto iter = staticObjectInfoList.begin(); iter != staticObjectInfoList.end(); ++iter)
		{
			if ((*iter).second->m_objectName == "WoodMarbleTop")
				continue;

			StaticObject* obj = new StaticObject((*iter).second->m_objectName);		
			m_objectList.emplace_back(obj);
			if (obj->Initialize((*iter).second->m_textureName) == false)
				return false;
			obj->SetPosition(VECTOR2D((*iter).second->m_x, (*iter).second->m_y));
		}

		for (auto iter = staticObjectInfoList.lower_bound("WoodMarbleTop"); iter != staticObjectInfoList.upper_bound("WoodMarbleTop"); ++iter)
		{
			Tile* obj = new Tile((*iter).second->m_objectName);
			m_tileTopList.emplace_back(obj);
			if (obj->Initialize((*iter).second->m_textureName) == false)
				return false;
			obj->SetPosition(VECTOR2D((*iter).second->m_x, (*iter).second->m_y));
			obj->SetTopPos();
		}
	}

	m_player = new Player("플레이어");
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

	AnimatedObject* object = m_player->FindObject("Body");
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
