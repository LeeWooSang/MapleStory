#pragma once
#include "../Scene.h"

enum OBJECT_KEY_TYPE
{
	BACKGROUND_KEY,
	FRAME_KEY,
	GAMEGRADE_KEY,
	LOGO_KEY,
	INPUT_BACKGROUND_KEY,
	LOGIN_BUTTON_KEY,
	ID_INPUT_KEY,
	PW_INPUT_KEY,
	QUIT_BUTTON_KEY,
	NOTICE_KEY
};

constexpr int MAX_OBJECT_TYPE = 8;

class LoginScene : public Scene
{
public:
	LoginScene();
	virtual ~LoginScene();

	virtual bool Initialize();
	virtual void Update(float);
	virtual void Render();
	virtual bool CheckCollision(int, int&);
	virtual void ProcessCollision(int, int);

	virtual void ProcessKeyboardMessage(HWND, UINT, WPARAM, LPARAM);

private:
	class Player* m_player;

	int m_inputKey;
};

enum OBJECT_TYPE
{
	LOGIN_BUTTON = 0x0001,
	ID_INPUT = 0x0002,
	PW_INPUT = 0x0004,
	QUIT_INPUT = 0x0008,
};

enum COLLISION_TYPE
{
	NO_COLLISION = 0x0010,
	COLLISION = 0x0020
};

enum MOUSE_TYPE
{
	NO_CLICLK = 0x0100,
	CLICK = 0x0200
};

enum PROCESS_OBJECT_COLLISION_TYPE
{
	LOGIN_BUTTON_NO_COLLISION_AND_NO_CLICK = 0x0111,
	LOGIN_BUTTON_NO_COLLISION_AND_CLICK = 0x0211,
	LOGIN_BUTTON_COLLISION_AND_NO_CLICK = 0x0121,
	LOGIN_BUTTON_COLLISION_AND_CLICK = 0x221,

	ID_INPUT_NO_COLLISION_AND_NO_CLICK = 0x0112,
	ID_INPUT_NO_COLLISION_AND_CLICK = 0x0212,
	ID_INPUT_COLLISION_AND_NO_CLICK = 0x0122,
	ID_INPUT_COLLISION_AND_CLICK = 0x0222,

	PW_INPUT_NO_COLLISION_AND_NO_CLICK = 0x0114,
	PW_INPUT_NO_COLLISION_AND_CLICK = 0x0214,
	PW_INPUT_COLLISION_AND_NO_CLICK = 0x0124,
	PW_INPUT_COLLISION_AND_CLICK = 0x0224,

	QUIT_INPUT_COLLISION_AND_CLICK = 0x0228
};