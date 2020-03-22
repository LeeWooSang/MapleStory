#pragma once
#include "../Defines.h"

class Scene
{
public:
	Scene() = default;
	virtual ~Scene();

	virtual bool Initialize() = 0;
	virtual void Update(float) = 0;
	virtual void Render() = 0;
	virtual void Release() = 0;

	class GameObject* FindObject(int) const;

protected:
	list<class GameObject*> m_ObjectList;
};