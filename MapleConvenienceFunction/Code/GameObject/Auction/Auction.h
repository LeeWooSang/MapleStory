#pragma once
#include "../GameObject.h"

class Auction : public GameObject
{
public:
	Auction(const string&);
	virtual ~Auction();

	virtual bool Initialize(void*);
	virtual void Update();

	void CalculateRatio(class Item*);
	
	void ShowItem();
	void Search();
	void Insert(class Item*);
	void Delete();

	bool MunicipalRatesMenu();

	void BuyItem();

private:
	// �޼� �ü�
	double m_mesoMunicipalRates;
	// ����� �Ǹ� ������
	double m_saleCommission;

	list<class Item*> m_itemList;

	class Player* m_player;
};