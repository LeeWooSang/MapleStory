#pragma once
#include "../AdventurerWarrior.h"

class Hero : public AdventurerWarrior
{
public:
	Hero(const string&);
	virtual ~Hero();

	virtual bool Initialize(void*);
	virtual void Update();
};

