#include "UI.h"

UI::UI(const string& name)
	: GameObject(name)
{
}

UI::~UI()
{
	cout << "UI - �Ҹ���" << endl;
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