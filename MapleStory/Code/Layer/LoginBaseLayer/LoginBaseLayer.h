#pragma once
#include "../Layer.h"

class LoginBaseLayer : public Layer
{
public:
	LoginBaseLayer();
	virtual ~LoginBaseLayer();

	virtual bool Initialize();
	virtual void Update(float);
	virtual void Render();

	virtual bool CheckCollision(class GameObject*, int&);
	virtual void ProcessCollision(class GameObject*, int&);
	virtual void ProcessKeyboardMessage(HWND, UINT, WPARAM, LPARAM);
};

enum BASE_OBJECT_KEY
{
	BACKGROUND = 0x0010,
	FRAME = 0x0020,
	GAMEGRADE = 0x0040,
	LOGO = 0x0080,
	INPUT_BACKGROUND = 0x0100
};