#include "Status.h"

Status::Status(const string& name)
	: GameObject(name)
{
	m_nickName.clear();
	m_level = 0;
	m_HP = 0;
	m_moveSpeed = 0;
	m_jumpAbility = 0;
}

Status::~Status()
{
}

bool Status::Initialize(void* p)
{
	return true;
}

void Status::Update()
{
}

void Status::ClearObjectInfo()
{
	m_nickName.clear();
	m_level = 0;
	m_HP = 0;
	m_moveSpeed = 0;
	m_jumpAbility = 0;
	GameObject::ClearObjectInfo();
}

void Status::SetStausInfo(const string& nickname, unsigned short level, unsigned int hp, unsigned char speed, unsigned char jump)
{
	m_nickName = nickname;
	m_level = level;
	m_HP = hp;
	m_moveSpeed = speed;
	m_jumpAbility = jump;
}

