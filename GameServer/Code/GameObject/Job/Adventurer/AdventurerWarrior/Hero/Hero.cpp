#include "Hero.h"

Hero::Hero(const string& name)
	: AdventurerWarrior(name)
{
}

Hero::~Hero()
{
}

bool Hero::Initialize(void*)
{
	return true;
}

void Hero::Update()
{
}
