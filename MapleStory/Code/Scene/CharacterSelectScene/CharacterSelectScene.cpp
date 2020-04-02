#include "CharacterSelectScene.h"
#include "../../Layer/CharacterSelectBaseLayer/CharacterSelectBaseLayer.h"

CharacterSelectScene::CharacterSelectScene()
{
}

CharacterSelectScene::~CharacterSelectScene()
{
}

bool CharacterSelectScene::Initialize()
{
	CharacterSelectBaseLayer* characterSelectBaseLayer = new CharacterSelectBaseLayer;
	m_layerList.emplace("CharacterSelectBaseLayer", characterSelectBaseLayer);
	if (characterSelectBaseLayer->Initialize() == false)
		return false;



	return true;
}

void CharacterSelectScene::Update(float elapsedTime)
{
}

void CharacterSelectScene::Render()
{
}

void CharacterSelectScene::ProcessKeyboardMessage(HWND, UINT, WPARAM, LPARAM)
{
}
