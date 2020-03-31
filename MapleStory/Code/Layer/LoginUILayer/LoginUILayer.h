#pragma once
#include "../Layer.h"

class LoginUILayer : public Layer
{
public:
	LoginUILayer();
	virtual ~LoginUILayer();

	virtual bool Initialize();
	virtual void Update(float);
	virtual void Render();

	virtual bool CheckCollision(class GameObject*, int&);
	virtual void ProcessCollision(class GameObject*, int&);
	virtual void ProcessKeyboardMessage(HWND, UINT, WPARAM, LPARAM);

private:
	int m_inputKey;
};

enum UI_OBJECT_KEY
{
	LOGIN_BUTTON = 0x0010,
	ID_INPUT = 0x0020,
	PW_INPUT = 0x0040,
	QUIT_INPUT = 0x0080,
};

enum PROCESS_UI_COLLISION_TYPE
{
	LOGIN_BUTTON_COLLISION_AND_CLICK = 0x001A,
	ID_INPUT_COLLISION_AND_CLICK = 0x002A,
	PW_INPUT_COLLISION_AND_CLICK = 0x004A,
	QUIT_INPUT_COLLISION_AND_CLICK = 0x008A
};