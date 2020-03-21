#include "NPC.h"

NPC::NPC(const string& name)
	: Character(name)
{
}

NPC::~NPC()
{
}

void NPC::ClearCharacterInfo()
{
	Character::ClearCharacterInfo();
}
