#include "SkillManager.h"
#include "Skill.h"
#include "../Status/PlayerStatus/PlayerStatus.h"

INIT_INSTACNE(SkillManager);
SkillManager::SkillManager()
{
	m_stat = nullptr;

	for (auto& data : m_linkSkillList)
		data = nullptr;
}

SkillManager::~SkillManager()
{
	for (auto data : m_linkSkillList)
	{
		if (data == nullptr)
			continue;

		delete data;
		data = nullptr;
	}
}

bool SkillManager::Initialize(PlayerStatus* stat)
{
	if (stat == nullptr)
		return false;
	m_stat = stat;



	return true;
}

void SkillManager::Update()
{
}

void SkillManager::CalculateLinkSkillLevel()
{
	unsigned char mylevel = m_stat->GetLevel();

	for (auto& data : m_linkSkillList)
	{
		if (data == nullptr)
			continue;

		if (mylevel >= 120)
		{
			data->SetSkillLevel(MAX_LINK_SKILL_LEVEL);
			continue;
		}
		else if (mylevel >= 70)
		{
			data->SetSkillLevel(MAX_LINK_SKILL_LEVEL - 1);
			continue;
		}

		data->SetSkillLevel(0);
	}
}

void SkillManager::CalculateLinkSkillEffect()
{
	int tempCritical = 0;

	for (auto data : m_linkSkillList)
	{
		if (data == nullptr)
			continue;

		switch (data->GetSkillEffect())
		{
		case LINK_SKILL_JOB::ADVENTURER_WARRIOR:
			{
			}
			break;

		case LINK_SKILL_JOB::ADVENTURER_ARCHER:
		{

		}
			break;

		case LINK_SKILL_JOB::ADVENTURER_MAGICIAN:
			break;

		case LINK_SKILL_JOB::ADVENTURER_THIEF:
			break;

		case LINK_SKILL_JOB::ADVENTURER_PIRATE:
			break;

		default:
			break;
		}
	}
}
