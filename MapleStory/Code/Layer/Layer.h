#pragma once
#include "../Defines.h"

class Layer
{
public:
	Layer();
	virtual ~Layer();

	virtual bool Initialize() = 0;
	virtual void Update(float) = 0;
	virtual void Render() = 0;

	virtual bool CheckCollision(class GameObject*, int&);
	virtual void ProcessCollision(class GameObject*, int&);
	virtual void ProcessKeyboardMessage(HWND, UINT, WPARAM, LPARAM) = 0;

	class GameObject* GetGameObject(int key);

protected:
	list<class GameObject*> m_objectList;
	unordered_map<int, class GameObject*> m_objectMap;
};

