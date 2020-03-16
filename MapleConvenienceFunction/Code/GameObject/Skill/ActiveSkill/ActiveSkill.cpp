#include "ActiveSkill.h"

ActiveSkill::ActiveSkill(const string& name)
	: Skill(name)
{
}

ActiveSkill::~ActiveSkill()
{
}

bool ActiveSkill::Initialize(void*)
{
	return true;
}

void ActiveSkill::Update()
{
}
