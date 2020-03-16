#pragma once
#include "../Status.h"

class PlayerStatus : public Status
{
public:
	PlayerStatus(const string&);
	virtual ~PlayerStatus();

	virtual bool Initialize(void*);
	virtual void Update();

	void AddStat(int, int, int, int, int, int, int);
	void AddDetailStat(int, int, int, int);

	void ShowStat()	const;

	unsigned int GetSTR()	const { return m_STR; }
	void SetSTR(unsigned int STR) { m_STR = STR; }

	unsigned int GetDEX()	const { return m_DEX; }
	void SetDEX(unsigned int DEX) { m_DEX = DEX; }

	unsigned int GetINT()	const { return m_INT; }
	void SetINT(unsigned int INT) { m_INT = INT; }

	unsigned int GetLUK()	const { return m_LUK; }
	void SetLUK(unsigned int LUK) { m_LUK = LUK; }

	void ArcaneSymoblEffect(class Job*);

private:
	unsigned int m_MP;

	unsigned int m_STR;
	unsigned int m_DEX;
	unsigned int m_INT;
	unsigned int m_LUK;

	unsigned char m_critical;
	unsigned char m_criticalDamage;
	unsigned short m_bossDamage;
	unsigned char m_defenceIgnore;

	unsigned char m_stance;

	unsigned short m_starForce;

	list<class ArcaneSymbol*> m_arcaneSymbolList;
	unsigned short m_totalArcaneForce;
};
