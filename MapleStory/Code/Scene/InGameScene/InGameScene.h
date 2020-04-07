#pragma once
#include "../Scene.h"

class InGameScene : public Scene
{
public:
	InGameScene();
	virtual ~InGameScene();

	virtual bool Initialize();
	virtual void Update(float);
	virtual void Render();

	virtual void ProcessKeyboardMessage(HWND, UINT, WPARAM, LPARAM);

private:
};

