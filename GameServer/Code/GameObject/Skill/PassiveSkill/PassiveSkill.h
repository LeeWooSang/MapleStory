#pragma once
#include "../Skill.h"

class PassiveSkill : public Skill
{
public:
	PassiveSkill(const string&);
	virtual ~PassiveSkill();

	virtual bool Initialize(void*);
	virtual void Update();
};

