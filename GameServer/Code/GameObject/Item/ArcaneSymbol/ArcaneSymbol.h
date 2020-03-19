#pragma once
#include "../Item.h"

class ArcaneSymbol : public Item
{
public:
	ArcaneSymbol(const string&);
	virtual ~ArcaneSymbol();

	virtual bool Initialize(void*);
	virtual void Update();

	void CalculateArcaneForce();

	unsigned short GetArcaneForce()	const { return m_arcaneForce; }
	void SetArcaneForce(unsigned short arcaneForce) { m_arcaneForce = arcaneForce; }

private:
	unsigned char m_symbolLevel;
	unsigned short m_arcaneForce;

	unsigned short m_levelUpNeeds;

	__int64 m_reinforcementMeso;
};

