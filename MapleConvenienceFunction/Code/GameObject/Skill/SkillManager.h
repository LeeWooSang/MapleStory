#pragma once
#include "../../Macro.h"
#include "../../Defines.h"

class SkillManager
{
	SINGLE_TONE(SkillManager)

public:
	bool Initialize(class PlayerStatus*);
	void Update();

	void CalculateLinkSkillLevel();
	void CalculateLinkSkillEffect();

private:
	PlayerStatus* m_stat;
	array<class Skill*, 12> m_linkSkillList;
};

// 링크 스킬관련 직업
enum LINK_SKILL_JOB
{
	ADVENTURER_WARRIOR	= 0x00000001,
	ADVENTURER_ARCHER	= 0x00000002,
	ADVENTURER_MAGICIAN= 0x00000004,
	ADVENTURER_THIEF		= 0x00000008,
	ADVENTURER_PIRATE		= 0x00000010,
	CYGNUS							= 0x00000020,
	MIHILE								= 0x00000040,
	RESISTANCE						= 0x00000080,
	DEMON_SLAYER				= 0x00000100,
	DEMON_AVENGER			= 0x00000200,
	XENON								= 0x00000400,
	ARAN								= 0x00000800,
	MERCEDES						= 0x00001000,
	LUMINOUS						= 0x00002000,
	PHANTOM						= 0x00004000,
	EUNWOL							= 0x00008000,
	KAISER								= 0x00010000,
	ANGELIC_BUSTER				= 0x00020000,
	CADENA							= 0x00040000,
	ADELE								= 0x00080000,
	ARK									= 0x00100000,
	ILLIUM								= 0x00200000,
	KINESIS								= 0x00400000,
	ZERO								= 0x00800000,
	HOYOUNG						= 0x01000000,
};

constexpr unsigned char MAX_LINK_SKILL_LEVEL = 2;