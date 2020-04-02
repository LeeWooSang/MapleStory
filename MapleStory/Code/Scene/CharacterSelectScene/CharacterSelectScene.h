#pragma once
#include "../Scene.h"

class CharacterSelectScene : public Scene
{
public:
	CharacterSelectScene();
	virtual ~CharacterSelectScene();

	virtual bool Initialize();
	virtual void Update(float);
	virtual void Render();

	virtual void ProcessKeyboardMessage(HWND, UINT, WPARAM, LPARAM);
};

