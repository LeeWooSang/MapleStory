#include "CharacterSelectUILayer.h"
#include "../../GameObject/UI/ButtonUI/ButtonUI.h"
#include "../../Scene/SceneManager.h"

CharacterSelectUILayer::CharacterSelectUILayer()
{
}

CharacterSelectUILayer::~CharacterSelectUILayer()
{
}

bool CharacterSelectUILayer::Initialize()
{
	string name = "GoWorldSelectSceneButton";
	ButtonUI* goWorldSelectSceneButton = new ButtonUI(name);
	m_objectMap.emplace(CHARACTER_SELECT_UI_OBJECT_KEY::GO_WORLD_SELECT_SCENE_BUTTON, goWorldSelectSceneButton);
	if (goWorldSelectSceneButton->Initialize() == false)
		return false;
	goWorldSelectSceneButton->SetPosition(VECTOR2D(-359.5f, 260.f));

	return true;
}

void CharacterSelectUILayer::Update(float elapsedTime)
{
	int flag = 0;
	for (auto object : m_objectMap)
	{
		flag = object.first;
		if (CheckCollision(object.second, flag) == false)
			continue;

		ProcessCollision(object.second, flag);
	}

	for (auto object : m_objectMap)
		object.second->Update(elapsedTime);
}

void CharacterSelectUILayer::Render()
{
	for (auto object : m_objectMap)
		object.second->Render();
}

bool CharacterSelectUILayer::CheckCollision(GameObject* object, int& flag)
{
	if (Layer::CheckCollision(object, flag) == false)
		return false;

	return true;
}

void CharacterSelectUILayer::ProcessCollision(GameObject* object, int& flag)
{
	switch (flag)
	{
	case PROCESS_CHARACTER_SELECT_UI_COLLISION_TYPE::GO_WORLD_SELECT_SCENE_BUTTON_COLLISION_AND_CLICK:
		GET_INSTANCE(SceneManager)->SetGameState(SceneManager::GAME_STATE::WORLD_SELECT_SCENE);
		break;

	default:
		break;
	}
}

void CharacterSelectUILayer::ProcessKeyboardMessage(HWND, UINT, WPARAM, LPARAM)
{
}
