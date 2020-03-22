#include "Framework.h"
#include "../GameTimer/GameTimer.h"

INIT_INSTACNE(Framework)
Framework::Framework()
{
}

Framework::~Framework()
{
	cout << "Framework - ¼Ò¸êÀÚ" << endl;
}

bool Framework::Initialize(HWND hWnd)
{
	GET_INSTANCE(GameTimer)->Reset();

	return true;
}

void Framework::Run()
{
	float elapsedTime = 0.f;

	GET_INSTANCE(GameTimer)->Tick(60.0);
	elapsedTime = GET_INSTANCE(GameTimer)->GetElapsedTime();

	Update(elapsedTime);
	//Render();
}

void Framework::Update(float elapsedTime)
{
}

void Framework::Render()
{
	//GET_INSTANCE(D2DManager)->GetRenderTarget()->BeginDraw();

	//D2D1_COLOR_F clearcolor = D2D1_COLOR_F{ 1.f, 1.f, 1.f, 1.f };
	//GET_INSTANCE(D2DManager)->GetRenderTarget()->Clear(&clearcolor);

	//GET_INSTANCE(SceneManager)->Render();
	//	
	//GET_INSTANCE(D2DManager)->GetRenderTarget()->EndDraw();
}