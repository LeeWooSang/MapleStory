#include "Chat.h"
#include"../../../D2DManager/D2DManager.h"
#include "../../../Input/Input.h"

Chat::Chat()
	: UI() 
{
}

Chat::~Chat()
{
	cout << "Chat - ¼Ò¸êÀÚ" << endl;
}

bool Chat::Initialize()
{
	if (GET_INSTANCE(D2DManager)->CreateTexture("ChatView", ImageInfo(L"../Resource/Textures/UI/ChatView.png", 640, 528, 1, 1, 0, 0, 400, 200)) == false)
		return false;

	m_WorldPosition = XMFLOAT2(-0.5f, -0.5f);

	return true;
}

void Chat::Update(float elapsedTime)
{
	UI::Update(elapsedTime);
}

void Chat::Render()
{
	UI::Render();

	float x = 10;
	float y = 300;
	int sizeX = 400;
	int sizeY = 100;
	D2D1_RECT_F textPos = { x, y, x + sizeX, y + sizeY };

	size_t len = GET_INSTANCE(Input)->GetText().length();
	float fontSize = 20.f;
	D2D1_RECT_F combPos = { x + fontSize * len, y, x + fontSize * len, y + sizeY };

	GET_INSTANCE(D2DManager)->Render("ChatView", m_WorldPosition);
	GET_INSTANCE(D2DManager)->Render(GET_INSTANCE(Input)->GetComb(), "¸ÞÀÌÇÃ", "Èò»ö", combPos);
	GET_INSTANCE(D2DManager)->Render(GET_INSTANCE(Input)->GetText(), "¸ÞÀÌÇÃ", "Èò»ö", textPos);
}

void Chat::Release()
{
	UI::Release();
}
