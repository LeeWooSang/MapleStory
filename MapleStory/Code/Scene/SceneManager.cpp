#include "SceneManager.h"
#include "../GameObject/Player/Player.h"
#include "InGameScene/InGameScene.h"

INIT_INSTACNE(SceneManager)

SceneManager::SceneManager()
{
}

SceneManager::~SceneManager()
{
	SAFE_DELETE_MAP(m_SceneList);

	cout << "SceneManager - ¼Ò¸êÀÚ" << endl;
}

bool SceneManager::Initialize()
{
	InGameScene* pInGameScene = new InGameScene;
	if (pInGameScene->Initialize() == false)
		return false;
	m_SceneList.emplace("InGameScene", pInGameScene);

	return true;
}

void SceneManager::Update(float elapsedTime)
{
	for (auto iter = m_SceneList.begin(); iter != m_SceneList.end(); ++iter)
	{
		(*iter).second->Update(elapsedTime);
	}
}

void SceneManager::Render()
{
	for (auto iter = m_SceneList.begin(); iter != m_SceneList.end(); ++iter)
	{
		(*iter).second->Render();
	}
}

InGameScene* SceneManager::GetInGameScene() const
{
	auto iter = m_SceneList.find("InGameScene");
	if (iter != m_SceneList.end())
		return reinterpret_cast<InGameScene*>((*iter).second);

	return nullptr;
}
