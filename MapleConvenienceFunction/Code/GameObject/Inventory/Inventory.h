#pragma once
#include "../GameObject.h"

struct Slot
{
	Slot() : m_item(nullptr), m_isEmpty(true)	{ }

	class Item* m_item;
	bool m_isEmpty;
};

constexpr unsigned char MAX_SLOT_SIZE = 125;

class Inventory : public GameObject
{
public:
	Inventory(const string&);
	virtual ~Inventory();

	virtual bool Initialize(void*);
	virtual void Update();

	bool AddInventory(class Item*);
	bool ResizeSlot(unsigned char);

	void ShowInventory() const;

	unsigned __int64 GetPlayerMeso()	const { return m_meso; }
	void SetPlayerMeso(unsigned __int64 meso) { m_meso = meso; }

private:
	Slot* m_slot;
	unsigned char m_slotSize;
	unsigned __int64 m_meso;
};

