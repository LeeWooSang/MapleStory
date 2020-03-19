#include "Item.h"

Item::Item(const string& name)
	: GameObject(name)
{
	m_cash = 0;
	m_meso = 0;
	m_ratio = 0;
	m_benefit = 0;
}

Item::~Item()
{
}

bool Item::Initialize(void* p)
{
	return true;
}

void Item::Update()
{
}

