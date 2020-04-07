#include "SceneManager.h"
#include "LoginScene/LoginScene.h"
#include "WorldSelectScene/WorldSelectScene.h"
#include "CharacterSelectScene/CharacterSelectScene.h"
#include "InGameScene/InGameScene.h"

INIT_INSTACNE(SceneManager)
SceneManager::SceneManager()
{
	m_sceneList.clear();
	//m_gameState = GAME_STATE::LOGIN_SCENE;
	//m_gameState = GAME_STATE::WORLD_SELECT_SCENE;
	//m_gameState = GAME_STATE::CHARACTER_SELECT_SCENE;
	m_gameState = GAME_STATE::INGAME_SCENE;
}

SceneManager::~SceneManager()
{
	SAFE_DELETE_MAP(m_sceneList);
}

bool SceneManager::Initialize()
{
	LoginScene* loginSc = new LoginScene;
	m_sceneList.emplace(GAME_STATE::LOGIN_SCENE, loginSc);
	if (loginSc->Initialize() == false)
		return false;
	
	WorldSelectScene* worldSelectSc = new WorldSelectScene;
	m_sceneList.emplace(GAME_STATE::WORLD_SELECT_SCENE, worldSelectSc);
	if (worldSelectSc->Initialize() == false)
		return false;

	CharacterSelectScene* characterSelectSc = new CharacterSelectScene;
	m_sceneList.emplace(GAME_STATE::CHARACTER_SELECT_SCENE, characterSelectSc);
	if (characterSelectSc->Initialize() == false)
		return false;

	InGameScene* inGameSc = new InGameScene;
	m_sceneList.emplace(GAME_STATE::INGAME_SCENE, inGameSc);
	if (inGameSc->Initialize() == false)
		return false;

	return true;
}

void SceneManager::Update(float elapsedTime)
{
	auto iter = m_sceneList.find(m_gameState);
	if (iter == m_sceneList.end())
		return;

	(*iter).second->Update(elapsedTime);
}

void SceneManager::Render()
{
	auto iter = m_sceneList.find(m_gameState);
	if (iter == m_sceneList.end())
		return;

	(*iter).second->Render();
}

Scene* SceneManager::GetScene()
{
	auto iter = m_sceneList.find(m_gameState);
	if(iter == m_sceneList.end())
		return nullptr;

	return (*iter).second;
}
