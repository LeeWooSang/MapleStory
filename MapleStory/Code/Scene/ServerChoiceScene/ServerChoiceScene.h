#pragma once
#include "../Scene.h"

class ServerChoiceScene : public Scene
{
public:
	ServerChoiceScene();
	virtual ~ServerChoiceScene();

	virtual bool Initialize();
	virtual void Update(float);
	virtual void Render();

	virtual void ProcessKeyboardMessage(HWND, UINT, WPARAM, LPARAM);
};

