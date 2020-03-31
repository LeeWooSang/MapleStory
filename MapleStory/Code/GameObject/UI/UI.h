#pragma once
#include "../GameObject.h"

class UI : public GameObject
{
public:
	UI(const string&);
	virtual ~UI();

	virtual bool Initialize();
	virtual void Update(float);
	virtual void Render();

	void CollideUIAndMouse(int&);

	enum COLLISION_TYPE
	{
		NO_COLLISION = 0x0001,
		COLLISION = 0x0002
	};

	enum MOUSE_TYPE
	{
		NO_CLICLK = 0x0004,
		CLICK = 0x0008
	};

protected:
};