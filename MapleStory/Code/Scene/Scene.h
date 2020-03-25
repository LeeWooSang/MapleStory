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

protected:
	unordered_map<string, class GameObject*> m_objectList;
};

