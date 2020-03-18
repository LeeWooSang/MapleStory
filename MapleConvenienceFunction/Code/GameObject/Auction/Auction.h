#pragma once
#include "../GameObject.h"

class Auction : public GameObject
{
public:
	Auction(const string&);
	virtual ~Auction();

	virtual bool Initialize(void*);
	virtual void Update();

	void CalculateRatioBenefit(class Item*);

	void ShowItem();
	void Search();
	void Insert(class Item*);
	void Delete();

	bool MunicipalRatesMenu();

	void BuyItem();

private:
	// 메소 시세
	double m_mesoMunicipalRates;
	// 경매장 판매 수수료
	double m_saleCommission;

	list<class Item*> m_itemList;
	class Player* m_player;
};