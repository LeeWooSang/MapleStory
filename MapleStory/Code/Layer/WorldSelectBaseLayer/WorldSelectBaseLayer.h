#pragma once
#include "../Layer.h"

class WorldSelectBaseLayer : public Layer
{
public:
	WorldSelectBaseLayer();
	virtual ~WorldSelectBaseLayer();

	virtual bool Initialize();
	virtual void Update(float);
	virtual void Render();

	virtual bool CheckCollision(class GameObject*, int&);
	virtual void ProcessCollision(class GameObject*, int&);
	virtual void ProcessKeyboardMessage(HWND, UINT, WPARAM, LPARAM);
};

