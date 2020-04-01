#pragma once
#include "../Layer.h"

class ChannelSelectLayer : public Layer
{
public:
	ChannelSelectLayer();
	virtual ~ChannelSelectLayer();

	virtual bool Initialize();
	virtual void Update(float);
	virtual void Render();

	virtual bool CheckCollision(class GameObject*, int&);
	virtual void ProcessCollision(class GameObject*, int&);
	virtual void ProcessKeyboardMessage(HWND, UINT, WPARAM, LPARAM);
};

enum CHANNEL_SELECT_OBJECT_KEY
{
	CHANNEL_BUTTON1 = 0x0010,
	CHANNEL_BUTTON2 = 0x0020,
	CHANNEL_BUTTON3 = 0x0040,
	CHANNEL_BUTTON4 = 0x0080,
	CHANNEL_BUTTON5 = 0x0100,
};

enum PROCESS_CHANNEL_SELECT_COLLISION_TYPE
{
	CHANNEL_BUTTON1_COLLISION_AND_CLICK = 0x001A,
	CHANNEL_BUTTON2_COLLISION_AND_CLICK = 0x002A,
	CHANNEL_BUTTON3_COLLISION_AND_CLICK = 0x004A,
	CHANNEL_BUTTON4_COLLISION_AND_CLICK = 0x008A,
	CHANNEL_BUTTON5_COLLISION_AND_CLICK = 0x010A,
};