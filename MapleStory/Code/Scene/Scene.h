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

	virtual void ProcessKeyboardMessage(HWND, UINT, WPARAM, LPARAM) = 0;

	class Layer* GetLayer(const string& key);
	//class GameObject* GetGameObject(int key)	 { return m_objectVector[key]; }

protected:
	unordered_map<string, class Layer*> m_layerList;
};

