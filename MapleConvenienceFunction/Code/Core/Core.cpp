#include "Core.h"
#include "../Resource/Resource.h"
#include "../DataBase/DataBase.h"
#include "../GameObject/Character/Player/Player.h"
#include "../GameObject/Auction/Auction.h"

// 메모리 릭이 있는지 알려준다.
#include <crtdbg.h>

INIT_INSTACNE(Core)
Core::Core()
{
	m_objectList.clear();

	// 메모리 릭이 있는지 체크를 해준다.
	// 릭이 있으면, 번호를 출력해준다.
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	// 출력된 번호를 넣어주면 그 지점으로 바로 이동시켜준다.
	// [ 예시 ]
	// Detected memory leaks!
	//	Dumping objects ->
	// {233} normal block at 0x000001469D91A680, 24 bytes long.
	// 233 이라는 지점에서 릭이 생김	
	//_CrtSetBreakAlloc(1061);
}

Core::~Core()
{
	GET_INSTANCE(Resource)->Release();
	GET_INSTANCE(DataBase)->Release();

	SAFE_DELETE_MAP(m_objectList);
}

bool Core::Initialize()
{
	if (GET_INSTANCE(Resource)->Initialize() == false)
		return false;

	if (GET_INSTANCE(DataBase)->Initialize() == false)
		return false;

	if (GET_INSTANCE(DataBase)->Connect() == false)
		return false;

	if (GET_INSTANCE(DataBase)->GetInventoryInfo() == false)
		return false;

	cout << endl;

	string name = "플레이어";
	Player* player = new Player(name);
	m_objectList.emplace(name, player);
	if (player->Initialize(nullptr) == false)
		return false;

	name = "경매장";
	Auction* auction = new Auction(name);
	m_objectList.emplace(name, auction);
	if (auction->Initialize(player) == false)
		return false;

	return true;
}

void Core::Update()
{
	bool check = true;

	while (check)
		check = MainMenu();
}

bool Core::MainMenu()
{
	bool check = true;
	string name = "";

	cout << "============= [ 메뉴 ] =============" << endl << endl;
	cout << "경매장" << endl;
	cout << "플레이어" << endl;
	cout << "====================================" << endl;
	cout << "입력 : ";
	cin >> name;
	cout << endl;

	auto iter = m_objectList.find(name);
	if (iter == m_objectList.end())
		return false;

	(*iter).second->Update();

	return true;
}