#pragma once
#include "../AnimatedObject.h"

class Character : public AnimatedObject
{
public:
	Character(const string&);
	virtual ~Character();

	virtual bool Initialize();
	virtual void Update(float);
	virtual void Render();
};

