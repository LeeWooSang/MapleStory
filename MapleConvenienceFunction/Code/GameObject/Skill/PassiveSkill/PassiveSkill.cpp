#include "PassiveSkill.h"

PassiveSkill::PassiveSkill(const string& name)
	: Skill(name)
{
}

PassiveSkill::~PassiveSkill()
{
}

bool PassiveSkill::Initialize(void *)
{
	return false;
}

void PassiveSkill::Update()
{
}
