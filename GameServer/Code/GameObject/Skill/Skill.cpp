#include "Skill.h"

Skill::Skill(const string& name)
	: GameObject(name)
{
	m_skillName = "";
	m_skillEffect = 0;
	m_skillLevel = 0;
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
