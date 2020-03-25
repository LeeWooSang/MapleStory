#include "Character.h"

Character::Character(const string& name)
	: GameObject(name)
{
}

Character::~Character()
{
}

bool Character::Initialize()
{
	return false;
}

void Character::Update(float)
{
}

void Character::Render()
{
}
