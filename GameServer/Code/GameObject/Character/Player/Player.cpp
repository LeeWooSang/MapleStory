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

	m_socket = 0;
	ZeroMemory(&m_packetBuf, sizeof(char));
	m_prevSize = 0;
	m_sendBytes = 0;
	m_isConnected = false;
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
	// ���Ͽ�
	m_uni = new Union("���Ͽ�");
	if (m_uni->Initialize(nullptr) == false)
		return false;

	m_myCharacter = m_uni->GetMyCharacter("â������");
	if (m_myCharacter == nullptr)
		return false;

	//�κ��丮
	unsigned char slotSize = 32;
	m_inventory = new Inventory("�κ��丮");
	if (m_inventory->Initialize(reinterpret_cast<void*>(slotSize)) == false)
		return false;

	// ����
	m_stat = new PlayerStatus("����");
	if (m_stat->Initialize(reinterpret_cast<void*>(m_myCharacter->m_level)) == false)
		return false;

	//if (GET_INSTANCE(SkillManager)->Initialize() == false)
	//	return false;

	cout << "�÷��̾� �ʱ�ȭ �Ϸ�" << endl;

	return true;
}

void Player::Update()
{
	char shortcut;
	cout << "============= [ �޴� ] =============" << endl;
	cout << "I. �κ��丮" << endl;
	cout << "S. ����" << endl;
	cout << "U. ���Ͽ�" << endl;
	cout << "====================================" << endl;
	cout << "�Է� : ";
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

void Player::ClearCharacterInfo()
{
	//wcscpy(m_PlayerID, L"");
	//m_X = START_X;
	//m_Y = START_Y;

	m_socket = 0;
	ZeroMemory(&m_packetBuf, sizeof(char));
	m_prevSize = 0;
	m_sendBytes = 0;
	m_isConnected = false;

	Character::ClearCharacterInfo();
}
