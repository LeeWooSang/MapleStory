#pragma once
#include "../Character.h"

class Player : public Character
{
public:
	Player(const string& name);
	virtual ~Player();

	virtual bool Initialize(void*);
	virtual void Update();

	class Inventory* GetInventory()		const { return m_inventory; }

private:
	class Job* m_job;
	class Union* m_uni;
	class Inventory* m_inventory;
};

