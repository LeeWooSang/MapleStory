#pragma once
#include "../Status.h"

class PlayerStatus : public Status
{
public:
	PlayerStatus(const string&);
	virtual ~PlayerStatus();

	virtual bool Initialize(void*);
	virtual void Update();
	virtual void ClearObjectInfo();

	void AddStat(int, int, int, int, int, int, int);
	void AddDetailStat(int, int, int, int);
	void SetDBdataToPlayerStatus(short, __int64, int, int, int, int, int, int);

	void ShowStat()	const;
	
	__int64 GetExp()	const { return m_exp; }

	int GetMP()	const { return m_MP; }

	int GetSTR()	const { return m_STR; }
	void SetSTR(unsigned int STR) { m_STR = STR; }

	int GetDEX()	const { return m_DEX; }
	void SetDEX(unsigned int DEX) { m_DEX = DEX; }

	int GetINT()	const { return m_INT; }
	void SetINT(unsigned int INT) { m_INT = INT; }

	int GetLUK()	const { return m_LUK; }
	void SetLUK(unsigned int LUK) { m_LUK = LUK; }

	void ArcaneSymoblEffect(class Job*);

private:
	__int64 m_exp;

	int m_MP;

	int m_STR;
	int m_DEX;
	int m_INT;
	int m_LUK;

	unsigned char m_Damage;

	unsigned char m_critical;
	unsigned char m_criticalDamage;
	unsigned short m_bossDamage;
	unsigned char m_defenceIgnore;

	unsigned char m_stance;

	unsigned short m_starForce;

	list<class ArcaneSymbol*> m_arcaneSymbolList;
	unsigned short m_totalArcaneForce;
};
