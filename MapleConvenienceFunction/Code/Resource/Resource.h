#pragma once
#include "../Macro.h"
#include "../Defines.h"

struct ItemInfo
{
	ItemInfo(const string& name, int cash)
		: m_name(name), m_cash(cash) {}
	string m_name;
	int m_cash;
};

struct JobInfo
{
	JobInfo(const string& name, unsigned char mainStat)
		: m_name(name), m_mainStat(mainStat) {}

	string m_name;
	unsigned char m_mainStat;
};

struct CharacterInfo
{
	CharacterInfo(const string& jobName, unsigned char level)
		: m_jobName(jobName), m_level(level) {}

	string m_jobName;
	unsigned char m_level;
};

struct UnionRaiderEffectInfo
{
	UnionRaiderEffectInfo(const string& name, const string& raiderEffect)
	: m_name(name), m_raiderEffect(raiderEffect) {}

	string m_name;
	string m_raiderEffect;
};

class Resource
{
	SINGLE_TONE(Resource)

public:
	bool Initialize();

	bool LoadItemInfo();
	bool SaveItemInfo();

	bool LoadJobInfo();
	bool SaveJobInfo();

	bool LoadCharacterInfo();
	bool SaveCharacterInfo();

	bool LoadUnionRaiderEffectInfo();
	bool SaveUnionRaiderEffectInfo();

	const list<ItemInfo*>& GetItemInfo() const { return m_itemInfoList; }
	const unordered_map<string, unsigned char>& GetJobInfo() const { return m_jobInfoList; }
	const unordered_map<string, CharacterInfo>& GetCharacterInfo() const { return m_characterInfoList; }
	const unordered_map<string, int>& GetUnionRaiderEffectInfo() const { return m_unionRaiderEffectList; }

private:
	list<ItemInfo*> m_itemInfoList;

	// Key : ����, Value : �ֽ���
	unordered_map<string, unsigned char> m_jobInfoList;

	// Key : �г���, Value : ĳ���� ����
	unordered_map<string, CharacterInfo> m_characterInfoList;

	// Key : ����, Value : ȿ��
	unordered_map<string, int> m_unionRaiderEffectList;
};

