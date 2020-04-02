#include "WorldSelectUILayer.h"
#include "../../GameObject/UI/ButtonUI/ButtonUI.h"
#include "../../Network/Network.h"
#include "../../Scene/SceneManager.h"
#include "../../Scene/WorldSelectScene/WorldSelectScene.h"

WorldSelectUILayer::WorldSelectUILayer()
{
}

WorldSelectUILayer::~WorldSelectUILayer()
{
}

bool WorldSelectUILayer::Initialize()
{
	string name = "GoLoginSceneButton";
	ButtonUI* goLoginSceneButton = new ButtonUI(name);
	m_objectMap.emplace(WORLD_SELECT_UI_OBJECT_KEY::GO_LOGIN_SCENE_BUTTON, goLoginSceneButton);
	if (goLoginSceneButton->Initialize() == false)
		return false;
	goLoginSceneButton->SetPosition(VECTOR2D(-359.5f, 260.f));

	name = "WorldButton0";
	ButtonUI* worldButton = new ButtonUI(name);
	m_objectMap.emplace(WORLD_SELECT_UI_OBJECT_KEY::WORLD_BUTTON, worldButton);
	if (worldButton->Initialize() == false)
		return false;
	worldButton->SetPosition(VECTOR2D(313.5f, -237.5f));

	return true;
}

void WorldSelectUILayer::Update(float elapsedTime)
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

void WorldSelectUILayer::Render()
{
	for (auto object : m_objectMap)
		object.second->Render();
}

bool WorldSelectUILayer::CheckCollision(GameObject* object, int& flag)
{
	if (Layer::CheckCollision(object, flag) == false)
		return false;

	return true;
}

void WorldSelectUILayer::ProcessCollision(GameObject* object, int& flag)
{
	switch (flag)
	{
	case PROCESS_WORLD_SELECT_UI_COLLISION_TYPE::GO_LOGIN_SCENE_BUTTON_COLLISION_AND_CLICK:
		GET_INSTANCE(Network)->SendServerLogoutPacket();
		GET_INSTANCE(SceneManager)->SetGameState(SceneManager::GAME_STATE::LOGIN_SCENE);
		cout << "뒤로 버튼 클릭" << endl;
		break;

	case PROCESS_WORLD_SELECT_UI_COLLISION_TYPE::WORLD_BUTTON_COLLISION_AND_CLICK:
		reinterpret_cast<WorldSelectScene*>(GET_INSTANCE(SceneManager)->GetScene())->SeleIsWorldSelect(true);
		cout << "월드 버튼 클릭" << endl;
		break;

	default:
		break;
	}
}

void WorldSelectUILayer::ProcessKeyboardMessage(HWND, UINT, WPARAM, LPARAM)
{
}
