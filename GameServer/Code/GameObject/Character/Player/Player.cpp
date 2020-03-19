#include "Player.h"
#include "../../Job/Job.h"
#include "../../Union/Union.h"
#include "../../Inventory/Inventory.h"
#include "../../Status/PlayerStatus/PlayerStatus.h"
#include "../../Skill/SkillManager.h"

Player::Player(const string& name)
	: Character(name)
{
	m_myCharacter = nullptr;
	m_uni = nullptr;
	m_inventory = nullptr;
}

Player::~Player()
{
	GET_INSTANCE(SkillManager)->Release();

	if (m_stat != nullptr)
	{
		delete m_stat;
		m_stat = nullptr;
	}

	if (m_inventory != nullptr)
	{
		delete m_inventory;
		m_inventory = nullptr;
	}

	if (m_uni != nullptr)
	{
		delete m_uni;
		m_uni = nullptr;
	}

	m_myCharacter = nullptr;
}

bool Player::Initialize(void* p)
{
	// 유니온
	m_uni = new Union("유니온");
	if (m_uni->Initialize(nullptr) == false)
		return false;

	m_myCharacter = m_uni->GetMyCharacter("창원기전");
	if (m_myCharacter == nullptr)
		return false;

	//인벤토리
	unsigned char slotSize = 32;
	m_inventory = new Inventory("인벤토리");
	if (m_inventory->Initialize(reinterpret_cast<void*>(slotSize)) == false)
		return false;

	// 스텟
	m_stat = new PlayerStatus("스텟");
	if (m_stat->Initialize(reinterpret_cast<void*>(m_myCharacter->m_level)) == false)
		return false;

	//if (GET_INSTANCE(SkillManager)->Initialize() == false)
	//	return false;

	cout << "플레이어 초기화 완료" << endl;

	return true;
}

void Player::Update()
{
	char shortcut;
	cout << "============= [ 메뉴 ] =============" << endl;
	cout << "I. 인벤토리" << endl;
	cout << "S. 스텟" << endl;
	cout << "U. 유니온" << endl;
	cout << "====================================" << endl;
	cout << "입력 : ";
	cin >> shortcut;
	cout << endl;

	switch (shortcut)
	{
	case 'i':
	case 'I':
		m_inventory->Update();
		break;

	case 's':
	case 'S':
		m_uni->CalculateUnionRaiderEffect(reinterpret_cast<PlayerStatus*>(m_stat));
		reinterpret_cast<PlayerStatus*>(m_stat)->ArcaneSymoblEffect(m_myCharacter->m_job);
		m_stat->Update();
		break;

	case 'u':
	case 'U':
		m_uni->Update();
		break;

	case 'k':
	case 'K':
		GET_INSTANCE(SkillManager)->Update();
		break;

	default:
		break;
	}
}
