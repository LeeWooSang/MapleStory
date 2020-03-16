#pragma once
#include "../GameObject.h"

class Character : public GameObject
{
public:
	Character(const string& name);
	virtual ~Character();

	virtual bool Initialize(void*);
	virtual void Update();

protected:
	class Status* m_stat;
};

