#pragma once
#include "../Adventurer.h"

class AdventurerWarrior : public Adventurer
{
public:
	AdventurerWarrior(const string&);
	virtual ~AdventurerWarrior();

	virtual bool Initialize(void*);
	virtual void Update();

protected:
};

