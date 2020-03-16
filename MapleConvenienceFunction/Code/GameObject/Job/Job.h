#pragma once
#include "../GameObject.h"

class Job : public GameObject
{
public:
	Job(const string&);
	virtual ~Job();

	virtual bool Initialize(void*);
	virtual void Update();

	int GetUnionRank()	const { return m_unionRank; }
	void SetUnionRank(int rank) { m_unionRank = rank; }
	
	int GetUnionRaiderEffect()	const { return m_unionRaiderEffect; }
	void SetUnionRaiderEffect(int effect) { m_unionRaiderEffect = effect; }

	enum MAIN_STAT
	{
		STR = 0x0001,
		DEX = 0x0002,
		INT = 0x0004,
		LUK = 0x0008,
		STR_DEX_LUK = 0x0010,
		HP = 0x0020
	};

	MAIN_STAT GetMainStat()	const { return m_mainStat; }

private:
	int m_unionRank;
	int m_unionRaiderEffect;

	// 직업군
	unsigned char m_jobKind;

	MAIN_STAT m_mainStat;
};

// 직업군 종류
enum JOB_KIND
{
	// 전사 직업군
	WARRIOR = 0x0001,
	ARCHER = 0x0002,
	WIZARD = 0x0004,
	THIEF = 0x0008
};
