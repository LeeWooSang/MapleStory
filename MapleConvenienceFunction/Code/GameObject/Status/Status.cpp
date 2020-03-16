#include "Status.h"

Status::Status(const string& name)
	: GameObject(name)
{
	m_nickName = "";
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
	m_level = reinterpret_cast<unsigned char>(p);


	return true;
}

void Status::Update()
{
}
