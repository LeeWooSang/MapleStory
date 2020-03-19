#include "PlayerStatus.h"
#include "../../Job/Job.h"
//#include "../../Item/ArcaneSymbol/ArcaneSymbol.h"

PlayerStatus::PlayerStatus(const string& name)
	: Status(name)
{
	m_MP = 0;

	m_STR = 0;
	m_DEX = 0;
	m_INT = 0;
	m_LUK = 0;

	m_Damage = 0;

	m_critical = 0;
	m_criticalDamage = 0;
	m_bossDamage = 0;
	m_defenceIgnore = 0;

	m_stance = 0;

	m_starForce = 0;

	m_arcaneSymbolList.clear();
	m_totalArcaneForce = 0;
}

PlayerStatus::~PlayerStatus()
{
	for (auto iter = m_arcaneSymbolList.begin(); iter != m_arcaneSymbolList.end(); )
	{
		delete (*iter);
		iter = m_arcaneSymbolList.erase(iter);
	}
	m_arcaneSymbolList.clear();
}

bool PlayerStatus::Initialize(void* p)
{
	if (p == nullptr)
		return false;

	Status::Initialize(p);

	//ArcaneSymbol* Vanishingjourney = new ArcaneSymbol("������ �ɺ� : �Ҹ��� ����");
	//m_arcaneSymbolList.emplace_back(Vanishingjourney);
	//if (Vanishingjourney->Initialize(nullptr) == false)
	//	return false;

	//ArcaneSymbol* Chewchewisland = new ArcaneSymbol("������ �ɺ� : ���� ���Ϸ���");
	//m_arcaneSymbolList.emplace_back(Chewchewisland);
	//if (Chewchewisland->Initialize(nullptr) == false)
	//	return false;


	//ArcaneSymbol* Lachenin = new ArcaneSymbol("������ �ɺ� : ���� ���� ���︥");
	//m_arcaneSymbolList.emplace_back(Lachenin);
	//if (Lachenin->Initialize(nullptr) == false)
	//	return false;

	//ArcaneSymbol* Arcana = new ArcaneSymbol("������ �ɺ� : �ź��� �� �Ƹ�ī��");
	//m_arcaneSymbolList.emplace_back(Arcana);
	//if (Arcana->Initialize(nullptr) == false)
	//	return false;

	//ArcaneSymbol* Morass = new ArcaneSymbol("������ �ɺ� : ����� �� ���");
	//m_arcaneSymbolList.emplace_back(Morass);
	//if (Morass->Initialize(nullptr) == false)
	//	return false;

	//ArcaneSymbol* Esfera = new ArcaneSymbol("������ �ɺ� : ������ �ٴ� �������");
	//m_arcaneSymbolList.emplace_back(Esfera);
	//if (Esfera->Initialize(nullptr) == false)
	//	return false;

	return true;
}

void PlayerStatus::Update()
{
	ShowStat();
}

void PlayerStatus::AddStat(int MaxHP, int MaxHP_Percent, int MaxMP_Percent, int STR, int DEX, int INT, int LUK)
{
	double tempHP_Percent = MaxHP_Percent;
	double tempMP_Percent = MaxMP_Percent;

	tempHP_Percent = 1.0 + tempHP_Percent * 0.01;
	m_HP = m_HP * tempHP_Percent + MaxHP;

	tempMP_Percent = 1.0 + tempMP_Percent * 0.01;
	m_MP *= tempMP_Percent;

	m_STR += STR;
	m_DEX += DEX;
	m_INT += INT;
	m_LUK += LUK;
}

void PlayerStatus::AddDetailStat(int critical, int criticalDamage, int bossDamage, int defenceIgnore)
{
	m_critical += critical;
	m_criticalDamage += criticalDamage;
	m_bossDamage += bossDamage;
	m_defenceIgnore += defenceIgnore;
}

void PlayerStatus::ShowStat()	const
{
	cout << "================= [����â] =================" << endl;
	cout << "HP : " << m_HP << "\tMP : " << m_MP << endl;
	cout << "STR : " << m_STR << "\tDEX : " << m_DEX << "\tINT : " << m_INT << "\tLUK : " << m_LUK << endl;
	cout << "ũ��Ƽ�� Ȯ�� : " << static_cast<int>(m_critical) << "\tũ��Ƽ�� ������ : " << static_cast<int>(m_criticalDamage) << endl;
	cout << "���� ������ : " << m_bossDamage << "\t����� ���� : " << static_cast<int>(m_defenceIgnore) << endl;
	cout << "���Ľ� : " << static_cast<int>(m_stance) << "\t�̵��ӵ� : " << static_cast<int>(m_moveSpeed) << "\t������ : " << static_cast<int>(m_jumpAbility) << endl;
	cout << "��Ÿ���� : " << m_starForce << "\t���������� : " << m_totalArcaneForce << endl;
	cout << "============================================" << endl;
}

void PlayerStatus::ArcaneSymoblEffect(Job* job)
{
	//// �� ������ ������ ����
	//for (auto iter = m_arcaneSymbolList.begin(); iter != m_arcaneSymbolList.end(); ++iter)
	//	m_totalArcaneForce += (*iter)->GetArcaneForce();

	// ���������� * 10�� �� ������ ��·�
	int mainStatIncrease = m_totalArcaneForce * 10;

	switch (job->GetMainStat())
	{
	case Job::MAIN_STAT::STR:
		m_STR += mainStatIncrease;
		break;

	case Job::MAIN_STAT::DEX:
		m_DEX += mainStatIncrease;
		break;

	case Job::MAIN_STAT::INT:
		m_INT += mainStatIncrease;
		break;

	case Job::MAIN_STAT::LUK:
		m_LUK += mainStatIncrease;
		break;

	case Job::MAIN_STAT::HP:
		break;

	case Job::MAIN_STAT::STR_DEX_LUK:
		break;
	}
}
