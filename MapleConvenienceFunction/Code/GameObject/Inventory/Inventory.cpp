#include "Inventory.h"
#include "../Item/Item.h"

Inventory::Inventory(const string& name)
	: GameObject(name)
{
	m_slot = nullptr;
	m_slotSize = 0;
	m_meso = 30000000000;
}

Inventory::~Inventory()
{
	for (int i = 0; i < m_slotSize; ++i)
	{
		if (m_slot[i].m_isEmpty == true)
			continue;
		
		delete m_slot[i].m_item;
		m_slot[i].m_item = nullptr;		
	}

	if (m_slot != nullptr)
	{
		delete[] m_slot;
		m_slot = nullptr;
	}
}

bool Inventory::Initialize(void* p)
{
	m_slotSize = reinterpret_cast<unsigned char>(p);
	
	if (m_slotSize <= 0)
		return false;

	m_slot = new Slot[m_slotSize];

	return true;
}

void Inventory::Update()
{
	ShowInventory();
}

bool Inventory::AddInventory(Item* item)
{
	// 아이템이 인벤토리에 저장되었는지 체크하는 변수
	bool check = false;

	// 1. 인벤토리에 빈 슬롯이 있는지 검사한다.
	// 2. 빈 슬롯에 아이템을 추가한다.
	// 3. 슬롯을 사용중으로 변경한다.
	for (int i = 0; i < m_slotSize; ++i)
	{
		if (m_slot[i].m_isEmpty == false)	
			continue;
		
		// 아이템을 복사함
		m_slot[i].m_item = item;
		m_slot[i].m_isEmpty = false;
		check = true;
		break;
	}

	if (check == false)
	{
		cout << "Inventory is full!" << endl;
		return false;
	}

	return true;
}

bool Inventory::ResizeSlot(unsigned char newSlotSize)
{
	if (m_slotSize >= MAX_SLOT_SIZE)
	{
		cout << "SlotCount of Inventory is Max Size!" << endl;
		return false;
	}

	// 1. 인벤토리의 슬롯 개수가 최대 크기인제 검사한다.
	// 2. 변경된 슬롯 개수만큼 공간을 다시 할당한다.
	// 3. 기존 슬롯의 데이터를 새로 할당한 슬롯에 복사한다.
	// 4. 기존 슬롯을 지움
	// 5. 현재 슬롯 개수를 변경한다.
	Slot* newSlot = new Slot[newSlotSize];

	for (int i = 0; i < m_slotSize; ++i)
	{
		if (m_slot[i].m_isEmpty == true)
			continue;

		newSlot[i] = m_slot[i];
	}

	delete[] m_slot;
	m_slot = newSlot;
	m_slotSize = newSlotSize;

	return true;
}

void Inventory::ShowInventory() const
{
	cout << "================= [인벤토리] =================" << endl;
	for (int i = 0; i < m_slotSize; ++i)
	{
		if (m_slot[i].m_isEmpty == true)
			continue;

		cout << "아이템 : " << m_slot[i].m_item->GetName() << endl;
	}
	cout << "메소 : " << m_meso << endl;
	cout << "==============================================" << endl;
}
