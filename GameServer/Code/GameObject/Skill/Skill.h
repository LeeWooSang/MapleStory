#pragma once
#include "../GameObject.h"

class Skill : public GameObject
{
public:
	Skill(const string&);
	virtual ~Skill();

	virtual bool Initialize(void*);
	virtual void Update();

	const string& GetSkillName()	const { return m_skillName; }
	void SetSkillName(const string& name) { m_skillName = name; }

	unsigned __int64 GetSkillEffect()	const { return m_skillEffect; }
	void SetSkillEffect(unsigned __int64 effect) { m_skillEffect = effect; }

	unsigned char GetSkillLevel()	const { return m_skillLevel; }
	void SetSkillLevel(unsigned char level) { m_skillLevel = level; }

protected:
	string m_skillName;
	unsigned __int64 m_skillEffect;
	unsigned char m_skillLevel;
};