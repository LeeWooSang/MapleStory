#include "Auction.h"
#include "../Character/Player/Player.h"
#include "../../Resource/Resource.h"
#include "../Item/Item.h"
#include "../Inventory/Inventory.h"

Auction::Auction(const string& name)
	: GameObject(name), m_mesoMunicipalRates(0), m_saleCommission(0)
{
	m_player = nullptr;
}

Auction::~Auction()
{
	m_player = nullptr;

	for (auto iter = m_itemList.begin(); iter != m_itemList.end(); )
	{
		if ((*iter) == nullptr)
		{
			++iter;
			continue;
		}

		delete (*iter);
		iter = m_itemList.erase(iter);
	}

	m_itemList.clear();
}

bool Auction::Initialize(void* p)
{
	if (p == nullptr)
		return false;
	m_player = reinterpret_cast<Player*>(p);

	cout << "1�� �޼� ����(��) : ";
	//cin >> m_mesoMunicipalRates;
	m_mesoMunicipalRates = 4000;
	cout << m_mesoMunicipalRates << endl;

	cout << "����� �Ǹ� ������ : ";
	//cin >> m_saleCommission;
	m_saleCommission = 5;
	cout << m_saleCommission << endl;

	list<CashItemInfo*> itemInfoList = GET_INSTANCE(Resource)->GetCashItemInfo();

	for (auto iter = itemInfoList.begin(); iter != itemInfoList.end(); ++iter)
	{
		Item* item = new Item((*iter)->m_name);
		m_itemList.emplace_back(item);
		if (item->Initialize(nullptr) == false)
			return false;
		item->SetCash((*iter)->m_cash);
	}

	for (auto iter = m_itemList.begin(); iter != m_itemList.end(); ++iter)
	{
		CalculateRatioBenefit((*iter));
	}


	cout << "����� �ʱ�ȭ �Ϸ�" << endl;

	return true;
}

void Auction::Update()
{
	MunicipalRatesMenu();
}

void Auction::CalculateRatioBenefit(Item* item)
{
	double commission = 1 - (m_saleCommission * 0.01);
	double ratio = 100000000 / m_mesoMunicipalRates;

	int cash = item->GetCash();	
	item->SetRatio(static_cast<__int64>(ratio) * cash);

	__int64 meso = item->GetMeso();
	double temp = (meso - item->GetRatio()) * commission;
	item->SetBenefit(static_cast<__int64>(temp));
}

void Auction::ShowItem()
{
	if (m_itemList.size() <= 0)
	{
		cout << "Auction is Empty!!!." << endl;
		return;
	}

	// �̵��� ���� ������ ����
	if (m_itemList.size() > 1)
		m_itemList.sort([](const Item* a, const Item* b) { return a->GetBenefit() > b->GetBenefit(); });

	string temp = "�� ���� : ";
	__int64 benefit = 0;

	cout << endl << "====================================================================================================" << endl;
	for (auto item : m_itemList)
	{
		benefit = item->GetBenefit();
		if (benefit < 0)
			temp = "�� ���� : ";

		cout << "�� ������ : " << item->GetName() << "     �� ĳ�� : " << item->GetCash() << "��     �� ���� : "
			<< item->GetRatio() << "�޼�     " << temp << benefit << "�޼�" << endl;
	}
	cout << "====================================================================================================" << endl << endl;
}

void Auction::Search()
{
	if (m_itemList.size() <= 0)
	{
		cout << "Auction is Empty!" << endl;
		return;
	}

	ShowItem();

	string name = "";
	cout << "������ ������ : ";
	cin.ignore();
	getline(cin, name);

	for (auto data : m_itemList)
	{
		if (data->GetName() == name)
		{
			__int64 meso = 0;
			cout << "������ ����� ���� : ";
			cin >> meso;
			data->SetMeso(meso);
			
			CalculateRatioBenefit(data);

			return;
		}
	}

	cout << "�˻��� �������� �����ϴ�." << endl;
}

void Auction::Insert(Item* item)
{
	CalculateRatioBenefit(item);
	m_itemList.emplace_back(item);
}

void Auction::Delete()
{
	
}

bool Auction::MunicipalRatesMenu()
{
	system("cls");

	int num = 0;

	cout << "============= [ �޴� ] =============" << endl << endl;
	cout << "1. ������ �����ϱ�" << endl;
	cout << "2. ����� ������ ��� ���" << endl;
	cout << "3. �˻�" << endl;
	cout << "4. ����" << endl;
	cout << "====================================" << endl << endl;
	cout << "��ȣ �Է� : ";
	cin >> num;
	cout << endl;

	system("cls");

	switch (num)
	{
	case 1:
		//CreateItem(auction);
		break;

	case 2:
		ShowItem();
		break;

	case 3:
		Search();
		break;

	case 4:
		BuyItem();
		break;

	default:
		break;
	}

	return true;
}

void Auction::BuyItem()
{
	ShowItem();

	// 1. �����Ϸ��� �������� �ִ��� ã�´�.
	// 2. �÷��̾��� �޼ҿ� ������ ������ ���Ѵ�.
	// 3. �÷��̾��� �κ��丮�� �������� �����Ѵ�.
	// 4. ����忡�� �������� �����Ѵ�.
	// 5. �÷��̾ ������ �� ������, �÷��̾��� �޼Ҹ� ���ݸ�ŭ ������Ų��.

	string name = "";
	cout << "������ ������ �̸� : ";
	cin.ignore();
	getline(cin, name);

	for (auto iter = m_itemList.begin(); iter != m_itemList.end(); )
	{
		if ((*iter)->GetName() != name)
		{
			++iter;
			continue;
		}

		Inventory* inven = m_player->GetInventory();
		unsigned __int64 playerMeso = inven->GetPlayerMeso();
		unsigned __int64 price = (*iter)->GetMeso();
		// �������� ã���� ��, �� �� �ִ��� �˻�
		if (playerMeso >= price)
		{
			// �������� �κ��丮�� �߰��Ѵ�.
			inven->AddInventory((*iter));
			// ����忡�� �������� �����Ѵ�.
			iter = m_itemList.erase(iter);
			// �÷��̾��� �޼Ҹ� ������Ų��.
			inven->SetPlayerMeso(playerMeso - price);

			cout << "������ �Ϸ�Ǿ����ϴ�." << endl;
		}
		else
			cout << "�޼Ұ� �����մϴ�." << endl;

		return;
	}

	cout << "�����Ϸ��� �������� �����ϴ�." << endl;
}
