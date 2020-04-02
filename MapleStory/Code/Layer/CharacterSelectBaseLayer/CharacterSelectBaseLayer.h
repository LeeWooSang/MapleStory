#pragma once
#include "../Layer.h"

class CharacterSelectBaseLayer : public Layer
{
public:
	CharacterSelectBaseLayer();
	virtual ~CharacterSelectBaseLayer();

	virtual bool Initialize();
	virtual void Update(float);
	virtual void Render();

	virtual bool CheckCollision(class GameObject*, int&);
	virtual void ProcessCollision(class GameObject*, int&);
	virtual void ProcessKeyboardMessage(HWND, UINT, WPARAM, LPARAM);
};

