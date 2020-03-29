#pragma once
#include "../Defines.h"

class Scene
{
public:
	Scene();
	virtual ~Scene();

	virtual bool Initialize() = 0;
	virtual void Update(float) = 0;
	virtual void Render() = 0;
	virtual bool CheckCollision(int, int&) = 0;
	virtual void ProcessCollision(int, int) = 0;

	virtual void ProcessKeyboardMessage(HWND, UINT, WPARAM, LPARAM) = 0;

	class GameObject* GetGameObject(int key)	 { return m_objectVector[key]; }

protected:
	unordered_map<string, class GameObject*> m_objectList;
	vector<class GameObject*> m_objectVector;
};

