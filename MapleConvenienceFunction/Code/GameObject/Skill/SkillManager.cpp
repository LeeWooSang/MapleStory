#include "SkillManager.h"
#include "Skill.h"
#include "../Status/PlayerStatus/PlayerStatus.h"

INIT_INSTACNE(SkillManager);
SkillManager::SkillManager()
{
}

SkillManager::~SkillManager()
{
}

bool SkillManager::Initialize()
{
	return true;
}

void SkillManager::Update()
{
}

void SkillManager::CalculateLinkSkillEffect()
{
	PlayerStatus* stat;

	for (auto data : m_linkSkillList)
	{
		if (data->m_isEmpty == true)
			continue;

		switch (data->m_skill->GetSkillEffect())
		{
		case LINK_SKILL_JOB::ADVENTURER_WARRIOR:
			{
			}
			break;

		case LINK_SKILL_JOB::ADVENTURER_ARCHER:
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
