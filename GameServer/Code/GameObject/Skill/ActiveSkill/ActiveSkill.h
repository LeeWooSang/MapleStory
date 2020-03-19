#pragma once
#include "../Skill.h"

class ActiveSkill : public Skill
{
public:
	ActiveSkill(const string&);
	virtual ~ActiveSkill();

	virtual bool Initialize(void*);
	virtual void Update();

};

