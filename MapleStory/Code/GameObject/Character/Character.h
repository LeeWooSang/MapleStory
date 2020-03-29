#pragma once
#include "../GameObject.h"

class Character : public GameObject
{
public:
	Character(const string&);
	virtual ~Character();

	virtual bool Initialize();
	virtual void Update(float);
	virtual void Render();
};

