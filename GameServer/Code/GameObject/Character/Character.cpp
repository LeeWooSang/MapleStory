#include "Character.h"

Character::Character(const string& name)
	: GameObject(name)
{
	m_stat = nullptr;
}

Character::~Character()
{
}

bool Character::Initialize(void*)
{
	return false;
}

void Character::Update()
{
}

