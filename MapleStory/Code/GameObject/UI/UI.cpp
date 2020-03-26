#include "UI.h"

UI::UI(const string& name)
	: GameObject(name)
{
}

UI::~UI()
{
	cout << "UI - ¼Ò¸êÀÚ" << endl;
}

bool UI::Initialize()
{
	return true;
}

bool UI::Initialize(TextureInfo info)
{
	return true;
}

void UI::Update(float elapsedTime)
{
}

void UI::Render()
{
}