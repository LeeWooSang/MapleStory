#pragma once
#include "../Character.h"

class NPC : public Character
{
public:
	NPC(const string&);
	virtual ~NPC();

	virtual void ClearCharacterInfo();
};

