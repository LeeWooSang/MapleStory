#pragma once
#include "../Layer.h"

class InGameBaseLayer : public Layer
{
public:
	InGameBaseLayer();
	virtual ~InGameBaseLayer();

	virtual bool Initialize();
	virtual void Update(float);
	virtual void Render();

	virtual bool CheckCollision(class GameObject*, int&);
	virtual void ProcessCollision(class GameObject*, int&);
	virtual void ProcessKeyboardMessage(HWND, UINT, WPARAM, LPARAM);

private:
	class Player* m_player;
};

