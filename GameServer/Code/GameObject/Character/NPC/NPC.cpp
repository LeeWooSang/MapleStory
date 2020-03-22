#include "NPC.h"

NPC::NPC(const string& name)
	: Character(name)
{
}

NPC::~NPC()
{
}

void NPC::ClearObjectInfo()
{
	Character::ClearObjectInfo();
}
