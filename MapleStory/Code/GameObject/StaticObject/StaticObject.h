#pragma once
#include "../GameObject.h"

class StaticObject : public GameObject
{
public:
	StaticObject(const string&);
	virtual ~StaticObject();

	virtual bool Initialize();
	virtual void Update(float) = 0;
	virtual void Render();
	virtual void RenderBoundingBox();
};

