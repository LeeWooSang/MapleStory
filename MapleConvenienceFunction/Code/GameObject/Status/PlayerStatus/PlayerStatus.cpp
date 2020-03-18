#include "PlayerStatus.h"
#include "../../Job/Job.h"
#include "../../Item/ArcaneSymbol/ArcaneSymbol.h"

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

	ArcaneSymbol* Vanishingjourney = new ArcaneSymbol("아케인 심볼 : 소멸의 여로");
	m_arcaneSymbolList.emplace_back(Vanishingjourney);
	if (Vanishingjourney->Initialize(nullptr) == false)
		return false;

	ArcaneSymbol* Chewchewisland = new ArcaneSymbol("아케인 심볼 : 츄츄 아일랜드");
	m_arcaneSymbolList.emplace_back(Chewchewisland);
	if (Chewchewisland->Initialize(nullptr) == false)
		return false;


	ArcaneSymbol* Lachenin = new ArcaneSymbol("아케인 심볼 : 꿈의 도시 레헬른");
	m_arcaneSymbolList.emplace_back(Lachenin);
	if (Lachenin->Initialize(nullptr) == false)
		return false;

	ArcaneSymbol* Arcana = new ArcaneSymbol("아케인 심볼 : 신비의 숲 아르카나");
	m_arcaneSymbolList.emplace_back(Arcana);
	if (Arcana->Initialize(nullptr) == false)
		return false;

	ArcaneSymbol* Morass = new ArcaneSymbol("아케인 심볼 : 기억의 늪 모라스");
	m_arcaneSymbolList.emplace_back(Morass);
	if (Morass->Initialize(nullptr) == false)
		return false;

	ArcaneSymbol* Esfera = new ArcaneSymbol("아케인 심볼 : 태초의 바다 에스페라");
	m_arcaneSymbolList.emplace_back(Esfera);
	if (Esfera->Initialize(nullptr) == false)
		return false;

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
	cout << "================= [스텟창] =================" << endl;
	cout << "HP : " << m_HP << "\tMP : " << m_MP << endl;
	cout << "STR : " << m_STR << "\tDEX : " << m_DEX << "\tINT : " << m_INT << "\tLUK : " << m_LUK << endl;
	cout << "크리티컬 확률 : " << static_cast<int>(m_critical) << "\t크리티컬 데미지 : " << static_cast<int>(m_criticalDamage) << endl;
	cout << "보스 데미지 : " << m_bossDamage << "\t방어율 무시 : " << static_cast<int>(m_defenceIgnore) << endl;
	cout << "스탠스 : " << static_cast<int>(m_stance) << "\t이동속도 : " << static_cast<int>(m_moveSpeed) << "\t점프력 : " << static_cast<int>(m_jumpAbility) << endl;
	cout << "스타포스 : " << m_starForce << "\t아케인포스 : " << m_totalArcaneForce << endl;
	cout << "============================================" << endl;
}

void PlayerStatus::ArcaneSymoblEffect(Job* job)
{
	// 총 아케인 포스를 구함
	for (auto iter = m_arcaneSymbolList.begin(); iter != m_arcaneSymbolList.end(); ++iter)
		m_totalArcaneForce += (*iter)->GetArcaneForce();

	// 아케인포스 * 10은 주 스텟의 상승량
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
