#include "WorldSelectScene.h"
#include "../../Layer/WorldSelectBaseLayer/WorldSelectBaseLayer.h"
#include "../../Layer/WorldSelectUILayer/WorldSelectUILayer.h"
#include "../../Layer/ChannelSelectLayer/ChannelSelectLayer.h"

WorldSelectScene::WorldSelectScene()
{
}

WorldSelectScene::~WorldSelectScene()
{
}

bool WorldSelectScene::Initialize()
{
	WorldSelectBaseLayer* worldSelectBaseLayer = new WorldSelectBaseLayer;
	m_layerList.emplace("WorldSelectBaseLayer", worldSelectBaseLayer);
	if (worldSelectBaseLayer->Initialize() == false)
		return false;

	WorldSelectUILayer* worldSelectUILayer = new WorldSelectUILayer;
	m_layerList.emplace("WorldSelectUILayer", worldSelectUILayer);
	if (worldSelectUILayer->Initialize() == false)
		return false;

	ChannelSelectLayer* channelSelectLayer = new ChannelSelectLayer;
	m_layerList.emplace("ChannelSelectLayer", channelSelectLayer);
	if (channelSelectLayer->Initialize() == false)
		return false;

	return true;
}

void WorldSelectScene::Update(float elapsedTime)
{
	for (auto layer : m_layerList)
		layer.second->Update(elapsedTime);
}

void WorldSelectScene::Render()
{
	for (auto layer : m_layerList)
		layer.second->Render();
}

void WorldSelectScene::ProcessKeyboardMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
}
