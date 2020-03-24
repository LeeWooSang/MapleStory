#include "Framework.h"
#include "../D2DManager/D2DManager.h"
#include "../GameTimer/GameTimer.h"
#include "../GameObject/Caret/Caret.h"

INIT_INSTACNE(Framework)
Framework::Framework()
{
}

Framework::~Framework()
{
	if (m_caret != nullptr)
	{
		delete m_caret;
		m_caret = nullptr;
	}

	GET_INSTANCE(GameTimer)->Release();
	GET_INSTANCE(D2DManager)->Release();

	cout << "Framework - ¼Ò¸êÀÚ" << endl;
}

bool Framework::Initialize(HWND hWnd)
{
	m_hWnd = hWnd;

	if (GET_INSTANCE(D2DManager)->Initialize(hWnd) == false)
		return false;

	GET_INSTANCE(GameTimer)->Reset();

	m_caret = new Caret;
	if (m_caret->Initialize() == false)
		return false;

	return true;
}

void Framework::Run()
{
	float elapsedTime = 0.f;

	GET_INSTANCE(GameTimer)->Tick(60.0);
	elapsedTime = GET_INSTANCE(GameTimer)->GetElapsedTime();

	Update(elapsedTime);
	Render();
}

void Framework::Update(float elapsedTime)
{
	m_caret->Update(elapsedTime);
}

void Framework::Render()
{
	GET_INSTANCE(D2DManager)->GetRenderTarget()->BeginDraw();

	D2D1_COLOR_F clearcolor = D2D1_COLOR_F{ 1.f, 1.f, 1.f, 1.f };
	GET_INSTANCE(D2DManager)->GetRenderTarget()->Clear(&clearcolor);

	m_caret->Render();
		
	GET_INSTANCE(D2DManager)->GetRenderTarget()->EndDraw();
}