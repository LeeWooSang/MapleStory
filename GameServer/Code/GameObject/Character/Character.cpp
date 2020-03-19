#include "Character.h"

Character::Character(const string& name)
	: GameObject(name)
{
	m_stat = nullptr;

	m_ID = 0;

	m_overEx.dataBuffer.len = MAX_BUFFER;
	m_overEx.dataBuffer.buf = m_overEx.messageBuffer;
	m_overEx.event_type = Core::EVENT_TYPE::RECV;
	//m_overEx.event_target_id = TARGET_IS_NONE;

	ZeroMemory(&m_overEx.overlapped, sizeof(WSAOVERLAPPED));
	m_viewList.clear();

	m_x = 0;
	m_y = 0;
}

Character::~Character()
{
}

bool Character::Initialize(void*)
{
	return false;
}

void Character::Update()
{
}

void Character::UpdatePosition(char dir)
{
	int x = m_x;
	int y = m_y;

	switch (dir)
	{
	case DIR_TYPE:: UP:
		--y;
		if (y < 0)
			y = 0;
		break;
	case DIR_TYPE::DOWN:
		++y;
		if (y >= WORLD_HEIGHT)
			y = WORLD_HEIGHT - 1;
		break;
	case DIR_TYPE::LEFT:
		if (x > 0)
			x--;
		break;
	case DIR_TYPE::RIGHT:
		if (x < WORLD_WIDTH - 1)
			x++;
		break;

	default:
		break;
	}

	m_x = x;
	m_y = y;
}
