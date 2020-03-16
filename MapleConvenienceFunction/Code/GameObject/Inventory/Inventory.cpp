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
	// �������� �κ��丮�� ����Ǿ����� üũ�ϴ� ����
	bool check = false;

	// 1. �κ��丮�� �� ������ �ִ��� �˻��Ѵ�.
	// 2. �� ���Կ� �������� �߰��Ѵ�.
	// 3. ������ ��������� �����Ѵ�.
	for (int i = 0; i < m_slotSize; ++i)
	{
		if (m_slot[i].m_isEmpty == false)	
			continue;
		
		// �������� ������
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

	// 1. �κ��丮�� ���� ������ �ִ� ũ������ �˻��Ѵ�.
	// 2. ����� ���� ������ŭ ������ �ٽ� �Ҵ��Ѵ�.
	// 3. ���� ������ �����͸� ���� �Ҵ��� ���Կ� �����Ѵ�.
	// 4. ���� ������ ����
	// 5. ���� ���� ������ �����Ѵ�.
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
	cout << "================= [�κ��丮] =================" << endl;
	for (int i = 0; i < m_slotSize; ++i)
	{
		if (m_slot[i].m_isEmpty == true)
			continue;

		cout << "������ : " << m_slot[i].m_item->GetName() << endl;
	}
	cout << "�޼� : " << m_meso << endl;
	cout << "==============================================" << endl;
}
