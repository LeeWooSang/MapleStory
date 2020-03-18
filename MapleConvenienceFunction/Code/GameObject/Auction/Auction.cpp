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

	cout << "1억 메소 가격(원) : ";
	//cin >> m_mesoMunicipalRates;
	m_mesoMunicipalRates = 4000;
	cout << m_mesoMunicipalRates << endl;

	cout << "경매장 판매 수수료 : ";
	//cin >> m_saleCommission;
	m_saleCommission = 5;
	cout << m_saleCommission << endl;

	list<CashItemInfo*> itemInfoList = GET_INSTANCE(Resource)->GetItemInfo();

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


	cout << "경매장 초기화 완료" << endl;

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

	// 이득이 높은 순서로 정렬
	if (m_itemList.size() > 1)
		m_itemList.sort([](const Item* a, const Item* b) { return a->GetBenefit() > b->GetBenefit(); });

	string temp = "▶ 이익 : ";
	__int64 benefit = 0;

	cout << endl << "====================================================================================================" << endl;
	for (auto item : m_itemList)
	{
		benefit = item->GetBenefit();
		if (benefit < 0)
			temp = "▶ 손해 : ";

		cout << "▶ 아이템 : " << item->GetName() << "     ▶ 캐시 : " << item->GetCash() << "원     ▶ 비율 : "
			<< item->GetRatio() << "메소     " << temp << benefit << "메소" << endl;
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
	cout << "수정할 아이템 : ";
	cin.ignore();
	getline(cin, name);

	for (auto data : m_itemList)
	{
		if (data->GetName() == name)
		{
			__int64 meso = 0;
			cout << "수정할 경매장 가격 : ";
			cin >> meso;
			data->SetMeso(meso);
			
			CalculateRatioBenefit(data);

			return;
		}
	}

	cout << "검색한 아이템이 없습니다." << endl;
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

	cout << "============= [ 메뉴 ] =============" << endl << endl;
	cout << "1. 아이템 생성하기" << endl;
	cout << "2. 경매장 아이템 모두 출력" << endl;
	cout << "3. 검색" << endl;
	cout << "4. 구입" << endl;
	cout << "====================================" << endl << endl;
	cout << "번호 입력 : ";
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

	// 1. 구입하려는 아이템이 있는지 찾는다.
	// 2. 플레이어의 메소와 아이템 가격을 비교한다.
	// 3. 플레이어의 인벤토리에 아이템을 복사한다.
	// 4. 경매장에서 아이템을 삭제한다.
	// 5. 플레이어가 구입할 수 있으면, 플레이어의 메소를 가격만큼 차감시킨다.

	string name = "";
	cout << "구입할 아이템 이름 : ";
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
		// 아이템을 찾았을 때, 살 수 있는지 검사
		if (playerMeso >= price)
		{
			// 아이템을 인벤토리에 추가한다.
			inven->AddInventory((*iter));
			// 경매장에서 아이템을 삭제한다.
			iter = m_itemList.erase(iter);
			// 플레이어의 메소를 차감시킨다.
			inven->SetPlayerMeso(playerMeso - price);

			cout << "구입이 완료되었습니다." << endl;
		}
		else
			cout << "메소가 부족합니다." << endl;

		return;
	}

	cout << "구입하려는 아이템이 없습니다." << endl;
}
