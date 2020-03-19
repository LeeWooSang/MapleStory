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

	const SOCKET& GetSocket()	const { return m_socket; }
	void SetSocket(const SOCKET& socket) { m_socket = socket; }

private:
	struct UnionCharaterInfo* m_myCharacter;

	class Union* m_uni;
	class Inventory* m_inventory;

	SOCKET m_socket;
};

