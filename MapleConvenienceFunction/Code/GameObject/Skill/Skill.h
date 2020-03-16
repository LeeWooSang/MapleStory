#pragma once
#include "../GameObject.h"

class Skill : public GameObject
{
public:
	Skill(const string&);
	virtual ~Skill();

	virtual bool Initialize(void*);
	virtual void Update();

	int GetSkillEffect()	const { return m_skillEffect; }

protected:
	string m_skillName;
	int m_skillEffect;
	unsigned char m_skillLevel;
};