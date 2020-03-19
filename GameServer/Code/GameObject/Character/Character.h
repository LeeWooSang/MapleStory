#pragma once
#include "../GameObject.h"
#include "../../Core/Core.h"

// 확장 오버렙트 구조체
struct OverEx
{
	WSAOVERLAPPED	overlapped;
	WSABUF					dataBuffer;
	char							messageBuffer[MAX_BUFFER];
	Core::EVENT_TYPE	event_type;
	int								event_target_id;
};

class Character : public GameObject
{
public:
	Character(const string& name);
	virtual ~Character();

	virtual bool Initialize(void*);
	virtual void Update();

	OverEx& GetOverEx() { return m_overEx; }

protected:
	class Status* m_stat;
	OverEx	m_overEx;
};

