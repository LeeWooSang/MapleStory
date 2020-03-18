#pragma once
#include "../Macro.h"
#include "../Defines.h"

struct NormalItemInfo
{
	NormalItemInfo(const string& name, unsigned short requestLevel)
		: m_name(name), m_requestLevel(requestLevel) {}

	string m_name;
	unsigned short m_requestLevel;
};

struct CashItemInfo
{
	CashItemInfo(const string& name, int cash, int size)
		: m_name(name), m_cash(cash), m_size(size) {}

	string m_name;
	int m_cash;
	int m_size;
};

struct JobInfo
{
	JobInfo(const string& occupationalCluster, const string& jobName, unsigned char mainStat, int unionRaiderEffect)
		: m_occupationalCluster(occupationalCluster), m_jobName(jobName), m_mainStat(mainStat), m_unionRaiderEffect(unionRaiderEffect) {}

	string m_occupationalCluster;
	string m_jobName;
	unsigned char m_mainStat;
	int m_unionRaiderEffect;
};

struct CharacterInfo
{
	CharacterInfo(const string& jobName, unsigned char level)
		: m_jobName(jobName), m_level(level) {}

	string m_jobName;
	unsigned char m_level;
};

class Resource
{
	SINGLE_TONE(Resource)

public:
	bool Initialize();

	bool LoadNormalItemInfo();
	bool LoadCashItemInfo();
	bool LoadJobInfo();
	bool LoadCharacterInfo();
	bool SaveCharacterInfo();

	const unordered_map<string, NormalItemInfo*>& GetNormalItemInfo() const { return m_normalItemInfoList; }
	void AddNormalItemInfo(const string& name, int requestLevel) { m_normalItemInfoList.emplace(name, new NormalItemInfo(name, requestLevel)); }

	const list<CashItemInfo*>& GetCashItemInfo() const { return m_cashItemInfoList; }
	void AddCashItemInfo(const string& name, int price, int size) { m_cashItemInfoList.emplace_back(new CashItemInfo(name, price, size)); }

	const unordered_map<string, JobInfo*>& GetJobInfo() const { return m_jobInfoList; }
	void AddJobInfo(const string& occupationalCluster, const string& jobName, int mainStat, int effect) { m_jobInfoList.emplace(jobName, new JobInfo(occupationalCluster, jobName, mainStat, effect)); }

	const unordered_map<string, CharacterInfo>& GetCharacterInfo() const { return m_characterInfoList; }

private:
	unordered_map<string, NormalItemInfo*> m_normalItemInfoList;

	list<CashItemInfo*> m_cashItemInfoList;

	// Key : 직업, Value : 직업정보
	unordered_map<string, JobInfo*> m_jobInfoList;

	// Key : 닉네임, Value : 캐릭터 정보
	unordered_map<string, CharacterInfo> m_characterInfoList;
};

