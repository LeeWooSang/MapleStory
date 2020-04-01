#pragma once
#include "../Scene.h"

class WorldSelectScene : public Scene
{
public:
	WorldSelectScene();
	virtual ~WorldSelectScene();

	virtual bool Initialize();
	virtual void Update(float);
	virtual void Render();

	virtual void ProcessKeyboardMessage(HWND, UINT, WPARAM, LPARAM);
};

