#pragma once
#include "../GameObject.h"

class StaticObject : public GameObject
{
public:
	StaticObject(const string&);
	virtual ~StaticObject();

	virtual bool Initialize();
	virtual bool Initialize(const string&);

	virtual void Update(float);
	virtual void Render();
	virtual void RenderBoundingBox();

protected:
	string m_textureName;
};

