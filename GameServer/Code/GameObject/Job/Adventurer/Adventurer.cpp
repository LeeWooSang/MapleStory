#include "Adventurer.h"

Adventurer::Adventurer(const string& name)
	: Job(name)
{
}

Adventurer::~Adventurer()
{
}

bool Adventurer::Initialize(void *)
{
	return true;
}

void Adventurer::Update()
{
}
