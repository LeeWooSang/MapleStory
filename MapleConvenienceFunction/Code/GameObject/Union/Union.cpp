#include "Union.h"
#include "../../Resource/Resource.h"
#include "../Job/Job.h"
#include "../Status/PlayerStatus/PlayerStatus.h"

Union::Union(const string& name)
	: GameObject(name), m_unionLevel(0), m_unionSize(0)
{
	m_unionCharacterList.clear();
}

Union::~Union()
{
	for (auto iter = m_unionCharacterList.begin(); iter != m_unionCharacterList.end(); ++iter)
	{
		if ((*iter)->m_job == nullptr)
			continue;

		delete (*iter)->m_job;
		(*iter)->m_job = nullptr;
	}

	SAFE_DELETE_LIST(m_unionCharacterList);
}

bool Union::Initialize(void* p)
{
	// 유니온 캐릭터 정보 저장
	auto characterInfo = GET_INSTANCE(Resource)->GetCharacterInfo();
	for (auto iter = characterInfo.begin(); iter != characterInfo.end(); ++iter)
	{
		Job* job = new Job((*iter).second.m_jobName);
		m_unionCharacterList.emplace_back(new UnionCharaterInfo((*iter).first, job, (*iter).second.m_level));
		if (job->Initialize(nullptr) == false)
			return false;
	}

	// 유니온 캐릭터에 맞는 공격대원 효과 저장
	auto raiderEffectInfo = GET_INSTANCE(Resource)->GetUnionRaiderEffectInfo();
	for (auto iter = m_unionCharacterList.begin(); iter != m_unionCharacterList.end(); ++iter)
	{
		auto iter2 = raiderEffectInfo.find((*iter)->m_job->GetName());
		if (iter2 == raiderEffectInfo.end())
			return false;
		(*iter)->m_job->SetUnionRaiderEffect((*iter2).second);
	}

	CalculateUnionLevel();
	CalculateUnionRank();

	return true;
}

void Union::Update()
{
	cout << "1. 유니온 리스트 출력" << endl;
	cout << "2. 유니온 추가" << endl;
	cout << "3. 유니온 리스트 저장" << endl;
	int num = 0;
	cin >> num;

	switch (num)
	{
	case 1:
		ShowUnion();
		break;

	case 2:
		break;

	case 3:
		break;

	default:
		break;
	}
}

void Union::CalculateUnionLevel()
{
	if (m_unionCharacterList.size() <= 0)
		return;

	else if (m_unionCharacterList.size() == 1)
	{
		auto iter = m_unionCharacterList.begin();
		m_unionLevel = (*iter)->m_level;

		m_unionSize = 1;

		return;
	}

	// 직업 레벨 순위 정렬
	m_unionCharacterList.sort([](const UnionCharaterInfo* a, const UnionCharaterInfo* b) { return a->m_level > b->m_level; });

	for (auto data : m_unionCharacterList)
	{
		if (data->m_level < 60)
			continue;
		
		if (m_unionSize == 40)
			break;

		m_unionLevel += data->m_level;
		++m_unionSize;
	}
}

void Union::CalculateUnionRank()
{
	for (auto data : m_unionCharacterList)
	{
		int rank = 0x0000;
		int level = data->m_level;

		if (level >= 250)
		{
			rank |= UNION_RANK::SSS;
		}
	
		else if (level >= 200)
		{
			rank |= UNION_RANK::SS;
		}

		else if (level >= 140)
		{
			rank |= UNION_RANK::S;
		}

		else if (level >= 100)
		{
			rank |= UNION_RANK::A;
		}

		else if (level >= 60)
		{
			rank |= UNION_RANK::B;
		}

		data->m_job->SetUnionRank(rank);
	}
}

void Union::CalculateUnionRaiderEffect(PlayerStatus* stat)
{
	int result = 0x0000;

	int tempSTR = 0;
	int tempDEX = 0;
	int tempINT= 0;
	int tempLUK = 0;

	int tempMaxHP_Percent = 0;
	int tempMaxMP_Percent = 0;

	int tempMaxHP = 0;

	int tempCritical = 0;
	int tempCriticalDamage = 0;

	int tempBossDamage = 0;
	int tempDefenceIgnore = 0;

	int tempExp = 0;
	int tempMeso = 0;

	for (auto data : m_unionCharacterList)
	{
		result |= data->m_job->GetUnionRank();
		result |= data->m_job->GetUnionRaiderEffect();
		
		switch (result)
		{
		case UNION_RANK_AND_RAIDER_EFFECT::B_STR:		tempSTR = 10;		break;
		case UNION_RANK_AND_RAIDER_EFFECT::A_STR:		tempSTR = 20;		break;
		case UNION_RANK_AND_RAIDER_EFFECT::S_STR:		tempSTR = 40;		break;
		case UNION_RANK_AND_RAIDER_EFFECT::SS_STR:		tempSTR = 80;		break;
		case UNION_RANK_AND_RAIDER_EFFECT::SSS_STR:		tempSTR = 100;	break;

		case UNION_RANK_AND_RAIDER_EFFECT::B_DEX:		tempDEX = 10;		break;
		case UNION_RANK_AND_RAIDER_EFFECT::A_DEX:		tempDEX = 20;		break;
		case UNION_RANK_AND_RAIDER_EFFECT::S_DEX:		tempDEX = 40;		break;
		case UNION_RANK_AND_RAIDER_EFFECT::SS_DEX:		tempDEX = 80;		break;
		case UNION_RANK_AND_RAIDER_EFFECT::SSS_DEX:	tempDEX = 100;	break;

		case UNION_RANK_AND_RAIDER_EFFECT::B_INT:			tempINT = 10;		break;
		case UNION_RANK_AND_RAIDER_EFFECT::A_INT:		tempINT = 20;		break;
		case UNION_RANK_AND_RAIDER_EFFECT::S_INT:			tempINT = 40;		break;
		case UNION_RANK_AND_RAIDER_EFFECT::SS_INT:		tempINT = 80;		break;
		case UNION_RANK_AND_RAIDER_EFFECT::SSS_INT:		tempINT = 100;		break;

		case UNION_RANK_AND_RAIDER_EFFECT::B_LUK:		tempLUK = 10;		break;
		case UNION_RANK_AND_RAIDER_EFFECT::A_LUK:		tempLUK = 20;		break;
		case UNION_RANK_AND_RAIDER_EFFECT::S_LUK:		tempLUK = 40;		break;
		case UNION_RANK_AND_RAIDER_EFFECT::SS_LUK:		tempLUK = 80;		break;
		case UNION_RANK_AND_RAIDER_EFFECT::SSS_LUK:	tempLUK = 100;	break;

		case UNION_RANK_AND_RAIDER_EFFECT::B_STR_DEX_LUK:			
			tempSTR = 5, tempDEX = 5, tempLUK = 5;			break;
		case UNION_RANK_AND_RAIDER_EFFECT::A_STR_DEX_LUK:		
			tempSTR = 10, tempDEX = 10, tempLUK = 10;		break;
		case UNION_RANK_AND_RAIDER_EFFECT::S_STR_DEX_LUK:			
			tempSTR = 20, tempDEX = 20, tempLUK = 20;		break;
		case UNION_RANK_AND_RAIDER_EFFECT::SS_STR_DEX_LUK:		
			tempSTR = 40, tempDEX = 40, tempLUK = 40;	break;
		case UNION_RANK_AND_RAIDER_EFFECT::SSS_STR_DEX_LUK:	
			tempSTR = 50, tempDEX = 50, tempLUK = 50;		break;

		case UNION_RANK_AND_RAIDER_EFFECT::B_MAX_HP_PERCENT:		tempMaxHP_Percent = 2;	break;
		case UNION_RANK_AND_RAIDER_EFFECT::A_MAX_HP_PERCENT:		tempMaxHP_Percent = 3;	break;
		case UNION_RANK_AND_RAIDER_EFFECT::S_MAX_HP_PERCENT:			tempMaxHP_Percent = 4;	break;
		case UNION_RANK_AND_RAIDER_EFFECT::SS_MAX_HP_PERCENT:		tempMaxHP_Percent = 5;	break;
		case UNION_RANK_AND_RAIDER_EFFECT::SSS_MAX_HP_PERCENT:		tempMaxHP_Percent = 6;	break;

		case UNION_RANK_AND_RAIDER_EFFECT::B_MAX_MP_PERCENT:		tempMaxMP_Percent = 2;	break;
		case UNION_RANK_AND_RAIDER_EFFECT::A_MAX_MP_PERCENT:		tempMaxMP_Percent = 3;	break;
		case UNION_RANK_AND_RAIDER_EFFECT::S_MAX_MP_PERCENT:		tempMaxMP_Percent = 4;	break;
		case UNION_RANK_AND_RAIDER_EFFECT::SS_MAX_MP_PERCENT:		tempMaxMP_Percent = 5;	break;
		case UNION_RANK_AND_RAIDER_EFFECT::SSS_MAX_MP_PERCENT:	tempMaxMP_Percent = 6;	break;

		case UNION_RANK_AND_RAIDER_EFFECT::B_MAX_HP:		tempMaxHP = 250;		break;
		case UNION_RANK_AND_RAIDER_EFFECT::A_MAX_HP:		tempMaxHP = 500;		break;
		case UNION_RANK_AND_RAIDER_EFFECT::S_MAX_HP:			tempMaxHP = 1000;	break;
		case UNION_RANK_AND_RAIDER_EFFECT::SS_MAX_HP:		tempMaxHP = 2000;	break;
		case UNION_RANK_AND_RAIDER_EFFECT::SSS_MAX_HP:		tempMaxHP = 2500;	break;

		case UNION_RANK_AND_RAIDER_EFFECT::B_CRITICAL:		tempCritical = 1; break;
		case UNION_RANK_AND_RAIDER_EFFECT::A_CRITICAL:		tempCritical = 2; break;
		case UNION_RANK_AND_RAIDER_EFFECT::S_CRITICAL:		tempCritical = 3; break;
		case UNION_RANK_AND_RAIDER_EFFECT::SS_CRITICAL:		tempCritical = 4; break;
		case UNION_RANK_AND_RAIDER_EFFECT::SSS_CRITICAL:	tempCritical = 5; break;

		case UNION_RANK_AND_RAIDER_EFFECT::B_CRITICAL_DAMAGE:		tempCriticalDamage = 1; break;
		case UNION_RANK_AND_RAIDER_EFFECT::A_CRITICAL_DAMAGE:		tempCriticalDamage = 2; break;
		case UNION_RANK_AND_RAIDER_EFFECT::S_CRITICAL_DAMAGE:		tempCriticalDamage = 3; break;
		case UNION_RANK_AND_RAIDER_EFFECT::SS_CRITICAL_DAMAGE:		tempCriticalDamage = 5; break;
		case UNION_RANK_AND_RAIDER_EFFECT::SSS_CRITICAL_DAMAGE:	tempCriticalDamage = 6; break;

		case UNION_RANK_AND_RAIDER_EFFECT::B_BOSS_DAMAGE:		tempBossDamage = 1; break;
		case UNION_RANK_AND_RAIDER_EFFECT::A_BOSS_DAMAGE:		tempBossDamage = 2; break;
		case UNION_RANK_AND_RAIDER_EFFECT::S_BOSS_DAMAGE:		tempBossDamage = 3; break;
		case UNION_RANK_AND_RAIDER_EFFECT::SS_BOSS_DAMAGE:	tempBossDamage = 5; break;
		case UNION_RANK_AND_RAIDER_EFFECT::SSS_BOSS_DAMAGE:	tempBossDamage = 6; break;

		case UNION_RANK_AND_RAIDER_EFFECT::B_DEFENCE_IGNORE:		tempDefenceIgnore = 1; break;
		case UNION_RANK_AND_RAIDER_EFFECT::A_DEFENCE_IGNORE:		tempDefenceIgnore = 2; break;
		case UNION_RANK_AND_RAIDER_EFFECT::S_DEFENCE_IGNORE:		tempDefenceIgnore = 3; break;
		case UNION_RANK_AND_RAIDER_EFFECT::SS_DEFENCE_IGNORE:	tempDefenceIgnore = 5; break;
		case UNION_RANK_AND_RAIDER_EFFECT::SSS_DEFENCE_IGNORE:	tempDefenceIgnore = 6; break;

		case UNION_RANK_AND_RAIDER_EFFECT::B_EXP:		tempExp = 4;	break;
		case UNION_RANK_AND_RAIDER_EFFECT::A_EXP:		tempExp = 6;	break;
		case UNION_RANK_AND_RAIDER_EFFECT::S_EXP:		tempExp = 8;	break;
		case UNION_RANK_AND_RAIDER_EFFECT::SS_EXP:		tempExp = 10;	break;
		case UNION_RANK_AND_RAIDER_EFFECT::SSS_EXP:	tempExp = 12;	break;

		case UNION_RANK_AND_RAIDER_EFFECT::B_MESO:		tempMeso = 1;		break;
		case UNION_RANK_AND_RAIDER_EFFECT::A_MESO:		tempMeso = 2;		break;
		case UNION_RANK_AND_RAIDER_EFFECT::S_MESO:			tempMeso = 3;		break;
		case UNION_RANK_AND_RAIDER_EFFECT::SS_MESO:		tempMeso = 4;		break;
		case UNION_RANK_AND_RAIDER_EFFECT::SSS_MESO:		tempMeso = 5;		break;

		default:
			break;
		}

		stat->AddStat(tempMaxHP, tempMaxHP_Percent, tempMaxMP_Percent, tempSTR, tempDEX, tempINT, tempLUK);
		stat->AddDetailStat(tempCritical, tempCriticalDamage, tempBossDamage, tempDefenceIgnore);

		result = 0x0000;
		tempSTR = 0;
		tempDEX = 0;
		tempINT = 0;
		tempLUK = 0;
		tempMaxHP_Percent = 0;
		tempMaxMP_Percent = 0;
		tempMaxHP = 0;
		tempCritical = 0;
		tempCriticalDamage = 0;
		tempBossDamage = 0;
		tempDefenceIgnore = 0;
		tempExp = 0;
		tempMeso = 0;
	}
}

void Union::ShowUnion()
{
	cout << "=============== [유니온] ===============" << endl;
	cout << "유니온 레벨 : " << m_unionLevel << endl;

	for (auto data : m_unionCharacterList)
		cout << "등급 : " << data->m_job->GetUnionRank() << ", 직업 : " << data->m_job->GetName() << ", 레벨 : " << static_cast<int>(data->m_level)
		<< ", 공격대원 효과 : " << data->m_job->GetUnionRaiderEffect() << endl;
	cout << "========================================" << endl;
}

void Union::AddUnionCharacter()
{
}

void Union::SaveUnionCharacter()
{
}

UnionCharaterInfo* Union::GetMyCharacter(const string& nickName)
{
	for (auto iter = m_unionCharacterList.begin(); iter != m_unionCharacterList.end(); ++iter)
	{
		if ((*iter)->m_nickName == nickName)
			return (*iter);
	}

	return nullptr;
}
