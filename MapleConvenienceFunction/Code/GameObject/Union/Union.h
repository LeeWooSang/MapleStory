#pragma once
#include "../GameObject.h"

struct UnionCharaterInfo
{
	UnionCharaterInfo(const string& nickName, class Job* job, unsigned char level)
		: m_nickName(nickName), m_job(job), m_level(level) {}

	string m_nickName;
	class Job* m_job;
	unsigned char m_level;
};

class Union : public GameObject
{
public:
	Union(const string&);
	virtual ~Union();

	virtual bool Initialize(void*);
	virtual void Update();

	// 유니온 레벨 계산
	void CalculateUnionLevel();
	// 유니온 등급 계산
	void CalculateUnionRank();

	// 공격대원 효과
	void CalculateUnionRaiderEffect(class PlayerStatus*);

	void ShowUnion();

	void AddUnionCharacter();
	void SaveUnionCharacter();

	UnionCharaterInfo* GetMyCharacter(const string&);

private:
	list<UnionCharaterInfo*> m_unionCharacterList;

	unsigned short m_unionLevel;
	int m_unionSize;

	enum UNION_RANK
	{
		B = 0x00000001,
		A = 0x00000002,
		S = 0x00000004,
		SS = 0x00000008,
		SSS = 0x00000010
	};

	enum UNION_RAIDER_EFFECT
	{
		STR = 0x00000020,
		DEX = 0x00000040,
		INT = 0x00000080,
		LUK = 0x00000100,

		STR_DEX_LUK = 0x00000200,

		MAX_HP_PERCENT = 0x00000400,
		MAX_MP_PERCENT = 0x00000800,
		MAX_HP = 0x00001000,

		CRITICAL = 0x00002000,
		CRITICAL_DAMAGE = 0x00004000,

		BOSS_DAMAGE = 0x00008000,
		DEFENCE_IGNORE = 0x00010000,

		EXP = 0x00020000,
		MESO = 0x00040000
	};

	enum UNION_RANK_AND_RAIDER_EFFECT
	{
		B_STR = 0x0021,
		A_STR = 0x0022,
		S_STR = 0x0024,
		SS_STR = 0x0028,
		SSS_STR = 0x0030,

		B_DEX = 0x0041,
		A_DEX = 0x0042,
		S_DEX = 0x0044,
		SS_DEX = 0x0048,
		SSS_DEX = 0x0050,

		B_INT = 0x0081,
		A_INT = 0x0082,
		S_INT = 0x0084,
		SS_INT = 0x0088,
		SSS_INT = 0x0090,

		B_LUK = 0x0101,
		A_LUK = 0x0102,
		S_LUK = 0x0104,
		SS_LUK = 0x0108,
		SSS_LUK = 0x0110,

		B_STR_DEX_LUK = 0x00000201,
		A_STR_DEX_LUK = 0x00000202,
		S_STR_DEX_LUK = 0x00000204,
		SS_STR_DEX_LUK = 0x00000208,
		SSS_STR_DEX_LUK = 0x00000210,

		B_MAX_HP_PERCENT = 0x00000401,
		A_MAX_HP_PERCENT = 0x00000402,
		S_MAX_HP_PERCENT = 0x00000404,
		SS_MAX_HP_PERCENT = 0x00000408,
		SSS_MAX_HP_PERCENT = 0x00000410,

		B_MAX_MP_PERCENT = 0x00000801,
		A_MAX_MP_PERCENT = 0x00000802,
		S_MAX_MP_PERCENT = 0x00000804,
		SS_MAX_MP_PERCENT = 0x00000808,
		SSS_MAX_MP_PERCENT = 0x00000810,

		B_MAX_HP = 0x00001001,
		A_MAX_HP = 0x00001002,
		S_MAX_HP = 0x00001004,
		SS_MAX_HP = 0x00001008,
		SSS_MAX_HP = 0x00001010,

		B_CRITICAL = 0x00002001,
		A_CRITICAL = 0x00002002,
		S_CRITICAL = 0x00002004,
		SS_CRITICAL = 0x00002008,
		SSS_CRITICAL = 0x00002010,

		B_CRITICAL_DAMAGE = 0x00004001,
		A_CRITICAL_DAMAGE = 0x00004002,
		S_CRITICAL_DAMAGE = 0x00004004,
		SS_CRITICAL_DAMAGE = 0x00004008,
		SSS_CRITICAL_DAMAGE = 0x00004010,

		B_BOSS_DAMAGE = 0x00008001,
		A_BOSS_DAMAGE = 0x00008002,
		S_BOSS_DAMAGE = 0x00008004,
		SS_BOSS_DAMAGE = 0x00008008,
		SSS_BOSS_DAMAGE = 0x00008010,

		B_DEFENCE_IGNORE = 0x00010001,
		A_DEFENCE_IGNORE = 0x00010002,
		S_DEFENCE_IGNORE = 0x00010004,
		SS_DEFENCE_IGNORE = 0x00010008,
		SSS_DEFENCE_IGNORE = 0x00010010,

		B_EXP = 0x00020001,
		A_EXP = 0x00020002,
		S_EXP = 0x00020004,
		SS_EXP = 0x00020008,
		SSS_EXP = 0x00020010,

		B_MESO = 0x00040001,
		A_MESO = 0x00040002,
		S_MESO = 0x00040004,
		SS_MESO = 0x00040008,
		SSS_MESO = 0x00040010
	};
};

