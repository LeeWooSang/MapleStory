#include "Core.h"
#include "../Resource/Resource.h"
#include "../GameObject/Character/Player/Player.h"
#include "../GameObject/Auction/Auction.h"

// �޸� ���� �ִ��� �˷��ش�.
#include <crtdbg.h>

INIT_INSTACNE(Core)
Core::Core()
{
	m_objectList.clear();

	// �޸� ���� �ִ��� üũ�� ���ش�.
	// ���� ������, ��ȣ�� ������ش�.
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	// ��µ� ��ȣ�� �־��ָ� �� �������� �ٷ� �̵������ش�.
	// [ ���� ]
	// Detected memory leaks!
	//	Dumping objects ->
	// {233} normal block at 0x000001469D91A680, 24 bytes long.
	// 233 �̶�� �������� ���� ����	
	//_CrtSetBreakAlloc(1061);
}

Core::~Core()
{
	GET_INSTANCE(Resource)->Release();
	SAFE_DELETE_MAP(m_objectList);
}

bool Core::Initialize()
{
	if (GET_INSTANCE(Resource)->Initialize() == false)
	{
		GET_INSTANCE(Resource)->Release();
		return false;
	}

	cout << endl;

	string name = "�÷��̾�";
	Player* player = new Player(name);
	m_objectList.emplace(name, player);
	if (player->Initialize(nullptr) == false)
		return false;

	name = "�����";
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

	cout << "============= [ �޴� ] =============" << endl << endl;
	cout << "�����" << endl;
	cout << "�÷��̾�" << endl;
	cout << "====================================" << endl;
	cout << "�Է� : ";
	cin >> name;
	cout << endl;

	auto iter = m_objectList.find(name);
	if (iter == m_objectList.end())
		return false;

	(*iter).second->Update();

	return true;
}