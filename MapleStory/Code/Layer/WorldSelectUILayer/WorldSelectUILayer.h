#pragma once
#include "../Layer.h"

class WorldSelectUILayer : public Layer
{
public:
	WorldSelectUILayer();
	virtual ~WorldSelectUILayer();

	virtual bool Initialize();
	virtual void Update(float);
	virtual void Render();

	virtual bool CheckCollision(class GameObject*, int&);
	virtual void ProcessCollision(class GameObject*, int&);
	virtual void ProcessKeyboardMessage(HWND, UINT, WPARAM, LPARAM);

private:
};

enum WORLD_SELECT_UI_OBJECT_KEY
{
	GO_LOGIN_SCENE_BUTTON = 0x0010,
	WORLD_BUTTON = 0x0020,

};

enum PROCESS_WORLD_SELECT_UI_COLLISION_TYPE
{
	GO_LOGIN_SCENE_BUTTON_COLLISION_AND_CLICK = 0x001A,
	WORLD_BUTTON_COLLISION_AND_CLICK = 0x002A,
};