#include "WorldSelectScene.h"
#include "../../Layer/WorldSelectBaseLayer/WorldSelectBaseLayer.h"
#include "../../Layer/WorldSelectUILayer/WorldSelectUILayer.h"
#include "../../Layer/ChannelSelectLayer/ChannelSelectLayer.h"

WorldSelectScene::WorldSelectScene()
{
	m_isWorldSelect = false;
	m_channelSelectLayer = nullptr;
}

WorldSelectScene::~WorldSelectScene()
{
}

bool WorldSelectScene::Initialize()
{
	m_isWorldSelect = false;

	WorldSelectBaseLayer* worldSelectBaseLayer = new WorldSelectBaseLayer;
	m_layerList.emplace("WorldSelectBaseLayer", worldSelectBaseLayer);
	if (worldSelectBaseLayer->Initialize() == false)
		return false;

	WorldSelectUILayer* worldSelectUILayer = new WorldSelectUILayer;
	m_layerList.emplace("WorldSelectUILayer", worldSelectUILayer);
	if (worldSelectUILayer->Initialize() == false)
		return false;

	m_channelSelectLayer = new ChannelSelectLayer;
	//m_layerList.emplace("ChannelSelectLayer", channelSelectLayer);
	if (m_channelSelectLayer->Initialize() == false)
		return false;

	return true;
}

void WorldSelectScene::Update(float elapsedTime)
{
	for (auto layer : m_layerList)
		layer.second->Update(elapsedTime);

	if (m_isWorldSelect == true)
	{
		m_channelSelectLayer->Update(elapsedTime);
	}
}

void WorldSelectScene::Render()
{
	for (auto layer : m_layerList)
		layer.second->Render();

	if (m_isWorldSelect == true)
	{
		m_channelSelectLayer->Render();
	}
}

void WorldSelectScene::ProcessKeyboardMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
}
