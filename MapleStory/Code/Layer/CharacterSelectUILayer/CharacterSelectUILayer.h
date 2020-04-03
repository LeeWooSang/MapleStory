#pragma once
#include "../Layer.h"

class CharacterSelectUILayer : public Layer
{
public:
	CharacterSelectUILayer();
	virtual ~CharacterSelectUILayer();

	virtual bool Initialize();
	virtual void Update(float);
	virtual void Render();

	virtual bool CheckCollision(class GameObject*, int&);
	virtual void ProcessCollision(class GameObject*, int&);
	virtual void ProcessKeyboardMessage(HWND, UINT, WPARAM, LPARAM);
};

enum CHARACTER_SELECT_UI_OBJECT_KEY
{
	GO_LOGIN_SCENE_BUTTON = 0x0010,
	GO_WORLD_SELECT_SCENE_BUTTON = 0x0020,

};

enum PROCESS_CHARACTER_SELECT_UI_COLLISION_TYPE
{
	GO_LOGIN_SCENE_BUTTON_COLLISION_AND_CLICK = 0x001A,
	GO_WORLD_SELECT_SCENE_BUTTON_COLLISION_AND_CLICK = 0x002A,


};