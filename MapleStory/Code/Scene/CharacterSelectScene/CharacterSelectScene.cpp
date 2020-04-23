#include "CharacterSelectScene.h"
#include "../../Layer/CharacterSelectBaseLayer/CharacterSelectBaseLayer.h"
#include "../../Layer/CharacterSelectUILayer/CharacterSelectUILayer.h"

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

	CharacterSelectUILayer* characterSelectUILayer = new CharacterSelectUILayer;
	m_layerList.emplace("CharacterSelectUILayer", characterSelectUILayer);
	if (characterSelectUILayer->Initialize() == false)
		return false;

	return true;
}

void CharacterSelectScene::Update(float elapsedTime)
{
	for (auto layer : m_layerList)
		layer.second->Update(elapsedTime);
}

void CharacterSelectScene::Render()
{
	for (auto layer : m_layerList)
		layer.second->Render();
}

void CharacterSelectScene::ProcessKeyboardMessage(HWND, UINT, WPARAM, LPARAM)
{
}
