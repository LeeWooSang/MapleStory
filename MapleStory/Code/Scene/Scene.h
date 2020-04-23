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

	void AddLayer(const string& key, class Layer* layer) { m_layerList.emplace(key, layer); }
	class Layer* GetLayer(const string& key);

protected:
	unordered_map<string, class Layer*> m_layerList;
};

