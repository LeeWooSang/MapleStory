#include "LoginScene.h"
#include "../../Layer/LoginBaseLayer/LoginBaseLayer.h"
#include "../../Layer/LoginUILayer/LoginUILayer.h"
#include "../../Layer/LoginNoticeLayer/LoginNoticeLayer.h"

LoginScene::LoginScene()
{
}

LoginScene::~LoginScene()
{
}

bool LoginScene::Initialize()
{
	LoginBaseLayer* loginBaseLayer = new LoginBaseLayer;
	m_layerList.emplace("LoginBaseLayer", loginBaseLayer);
	if (loginBaseLayer->Initialize() == false)
		return false;

	LoginUILayer* loginUILayer = new LoginUILayer;
	m_layerList.emplace("LoginUILayer", loginUILayer);
	if (loginUILayer->Initialize() == false)
		return false;

	LoginNoticeLayer* loginNoticeLayer = new LoginNoticeLayer;
	m_layerList.emplace("LoginNoticeLayer", loginNoticeLayer);
	if (loginNoticeLayer->Initialize() == false)
		return false;

	//name = "Player";
	//m_player = new Player(name);
	//if(m_player->Initialize(TextureInfo(L"../Resource/Textures/Character/Player.png", 133, 144, 1, 1, 0, 0)) == false)
	//	return false;

	return true;
}

void LoginScene::Update(float elapsedTime)
{
	for (auto layer : m_layerList)
		layer.second->Update(elapsedTime);
}

void LoginScene::Render()
{
	for (auto layer : m_layerList)
		layer.second->Render();
}

void LoginScene::ProcessKeyboardMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	for(auto layer : m_layerList)
		layer.second->ProcessKeyboardMessage(hWnd, message, wParam, lParam);

	//auto iter = m_layerList.find("LoginUILayer");
	//if (iter == m_layerList.end())
	//	return;

	//(*iter).second->ProcessKeyboardMessage(hWnd, message, wParam, lParam);
}