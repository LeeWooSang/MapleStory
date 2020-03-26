#pragma once
#include "../GameObject.h"

class UI : public GameObject
{
public:
	UI(const string&);
	virtual ~UI();

	virtual bool Initialize();
	virtual bool Initialize(TextureInfo);
	virtual void Update(float);
	virtual void Render();

protected:

};