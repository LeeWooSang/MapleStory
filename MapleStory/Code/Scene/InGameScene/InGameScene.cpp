#include "InGameScene.h"
#include "../../Layer/InGameBaseLayer/InGameBaseLayer.h"

InGameScene::InGameScene()
{
}

InGameScene::~InGameScene()
{
}

bool InGameScene::Initialize()
{
	InGameBaseLayer* inGameBaseLayer = new InGameBaseLayer;
	m_layerList.emplace("InGameBaseLayer", inGameBaseLayer);
	if (inGameBaseLayer->Initialize() == false)
		return false;

	return true;
}

void InGameScene::Update(float elapsedTime)
{
	for (auto layer : m_layerList)
		layer.second->Update(elapsedTime);
}

void InGameScene::Render()
{
	for (auto layer : m_layerList)
		layer.second->Render();
}

void InGameScene::ProcessKeyboardMessage(HWND, UINT, WPARAM, LPARAM)
{
}
