#include "CharacterSelectScene.h"
#include "../../Layer/CharacterSelectBaseLayer/CharacterSelectBaseLayer.h"
#include "../../Layer/CharacterSelectUILayer/CharacterSelectUILayer.h"
#include "../../GameObject/Character/Player/Player.h"

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

	m_player = new Player("ChannelGauge");
	if (m_player->Initialize() == false)
		return false;
	m_player->InitAnimation();

	return true;
}

void CharacterSelectScene::Update(float elapsedTime)
{
	for (auto layer : m_layerList)
		layer.second->Update(elapsedTime);

	if (m_player != nullptr)
		m_player->Update(elapsedTime);
}

void CharacterSelectScene::Render()
{
	for (auto layer : m_layerList)
		layer.second->Render();

	if (m_player != nullptr)
		m_player->Render();
}

void CharacterSelectScene::ProcessKeyboardMessage(HWND, UINT, WPARAM, LPARAM)
{
}
