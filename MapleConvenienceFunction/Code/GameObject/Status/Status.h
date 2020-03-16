#pragma once
#include "../GameObject.h"

class Status : public GameObject
{
public:
	Status(const string&);
	virtual ~Status();

	virtual bool Initialize(void*);
	virtual void Update();

	const string& GetNickName()	const { return m_nickName; }
	unsigned char GetLevel()	const { return m_level; }

protected:
	string m_nickName;
	unsigned char m_level;
	unsigned int m_HP;
	unsigned char m_moveSpeed;
	unsigned char m_jumpAbility;
};