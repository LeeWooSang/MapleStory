#pragma once
#include "../GameObject.h"

class Item : public GameObject
{
public:
	Item(const string&);
	virtual ~Item();

	virtual bool Initialize(void*);
	virtual void Update();

	const string& GetName() { return m_name; }
	
	int GetCash()	const { return m_cash; }
	void SetCash(int cash) { m_cash = cash; }

	__int64 GetMeso()	const { return m_meso; }
	void SetMeso(__int64 meso) { m_meso = meso; }

	__int64 GetRatio()	const { return m_ratio; }
	void SetRatio(__int64 ratio)	{ m_ratio = ratio; }

	__int64 GetBenefit() const { return m_benefit; }
	void SetBenefit(__int64 benefit) { m_benefit = benefit; }

private:
	int m_cash;
	__int64 m_meso;
	__int64 m_ratio;
	__int64 m_benefit;
};
