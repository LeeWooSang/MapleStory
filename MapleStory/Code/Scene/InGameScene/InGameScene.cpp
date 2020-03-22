#include "InGameScene.h"
#include "../../Macro.h"
#include "../../GameObject/Map/Map.h"
#include "../../GameObject/Monster/Monster.h"
#include "../../GameObject/Player/Player.h"
#include "../../GameObject/UI/Chat/Chat.h"
#include "../../Camera/Camera.h"

InGameScene::InGameScene()
	: m_Player(nullptr)
{
}

InGameScene::~InGameScene()
{
	Release();

	cout << "InGameScene ¼Ò¸êÀÚ" << endl;
}

bool InGameScene::Initialize()
{
	Map* pMap = new Map;
	if (pMap->Initialize() == false)
		return false;
	m_ObjectList.emplace_back(pMap);

	Monster* pMonster = new Monster;
	if (pMonster->Initialize() == false)
		return false;
	m_ObjectList.emplace_back(pMonster);

	Chat* pChatUI = new Chat;
	if (pChatUI->Initialize() == false)
		return false;
	m_ObjectList.emplace_back(pChatUI);

	m_Player = new Player;
	if (m_Player->Initialize() == false)
		return false;

	return true;
}

void InGameScene::Update(float elapsedTime)
{
	for (auto iter = m_ObjectList.begin(); iter != m_ObjectList.end(); ++iter)
		(*iter)->Update(elapsedTime);

	m_Player->Update(elapsedTime);
	//cout << m_Player->GetWorldPosition().x << ", " << m_Player->GetWorldPosition().y << endl;
}

void InGameScene::Render()
{
	for (auto iter = m_ObjectList.begin(); iter != m_ObjectList.end(); ++iter)
		(*iter)->Render();

	m_Player->Render();
}

void InGameScene::Release()
{
	SAFE_DELETE_LIST(m_ObjectList);

	SAFE_DELETE(m_Player);
}
