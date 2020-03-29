#include "Framework.h"
#include "../D2DManager/D2DManager.h"
#include "../ResourceManager/ResourceManager.h"
#include "../GameTimer/GameTimer.h"
#include "../Network/Network.h"
#include "../Camera/Camera.h"
#include "../Scene/SceneManager.h"

INIT_INSTACNE(Framework)
Framework::Framework()
{
	m_hwnd = nullptr;
	m_titleName.clear();
}

Framework::~Framework()
{
	GET_INSTANCE(SceneManager)->Release();
	GET_INSTANCE(Camera)->Release();
	GET_INSTANCE(Network)->Release();
	GET_INSTANCE(GameTimer)->Release();
	GET_INSTANCE(ResourceManager)->Release();
	GET_INSTANCE(D2DManager)->Release();
}

bool Framework::Initialize(HWND hWnd)
{
	m_hwnd = hWnd;
	m_titleName = L"MapleStory ";

	if (GET_INSTANCE(D2DManager)->Initialize(hWnd) == false)
		return false;

	if (GET_INSTANCE(ResourceManager)->Initialize() == false)
		return false;

	GET_INSTANCE(GameTimer)->Reset();

	if (GET_INSTANCE(Network)->Initialize() == false)
		return false;

	if (GET_INSTANCE(Camera)->Initialize() == false)
		return false;

	if (GET_INSTANCE(SceneManager)->Initialize() == false)
		return false;

	return true;
}

void Framework::Run()
{
	GET_INSTANCE(GameTimer)->Tick(0);

	Update(GET_INSTANCE(GameTimer)->GetElapsedTime());
	Render();

	wstring titleName = m_titleName + to_wstring(GET_INSTANCE(GameTimer)->GetFrameRate()) + L" FPS";
	::SetWindowText(m_hwnd, const_cast<wchar_t*>(titleName.c_str()));
}

void Framework::Update(float elapsedTime)
{
	GET_INSTANCE(SceneManager)->Update(elapsedTime);
}

void Framework::Render()
{
	GET_INSTANCE(D2DManager)->GetRenderTarget()->BeginDraw();
	GET_INSTANCE(D2DManager)->GetRenderTarget()->Clear(D2D1::ColorF(D2D1::ColorF::Black));

	GET_INSTANCE(SceneManager)->Render();
		
	GET_INSTANCE(D2DManager)->GetRenderTarget()->EndDraw();
}