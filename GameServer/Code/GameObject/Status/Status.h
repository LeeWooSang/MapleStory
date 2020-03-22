#pragma once
#include "../GameObject.h"

class Status : public GameObject
{
public:
	Status(const string&);
	virtual ~Status();

	virtual bool Initialize(void*);
	virtual void Update();
	virtual void ClearObjectInfo();

	const string& GetNickName()	const { return m_nickName; }
	void SetNickName(const string& nickName) { m_nickName = nickName; }

	short GetLevel()	const { return m_level; }
	int GetHP()	const { return m_HP; }
	char GetMoveSpeed()	const { return m_moveSpeed; }
	char GetJumpAbility()	const { return m_jumpAbility; }

	void SetStausInfo(const string&, unsigned short, unsigned int, unsigned char, unsigned char);

protected:
	string m_nickName;

	short m_level;
	int m_HP;
	char m_moveSpeed;
	char m_jumpAbility;
};