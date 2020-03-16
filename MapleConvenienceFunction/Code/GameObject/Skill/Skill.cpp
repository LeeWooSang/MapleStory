#include "Skill.h"

Skill::Skill(const string& name)
	: GameObject(name)
{
	m_skillName = "";
}

Skill::~Skill()
{
}

bool Skill::Initialize(void* p)
{
	return true;
}

void Skill::Update()
{
}
