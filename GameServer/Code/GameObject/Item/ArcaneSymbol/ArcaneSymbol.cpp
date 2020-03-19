#include "ArcaneSymbol.h"
#include "../../../Resource/Resource.h"
#include "../../Status/Status.h"
#include "../../Job/Job.h"

ArcaneSymbol::ArcaneSymbol(const string& name)
	: Item(name)
{
	m_symbolLevel = 0;
	m_arcaneForce = 0;
	m_reinforcementMeso = 0;
}

ArcaneSymbol::~ArcaneSymbol()
{
}

bool ArcaneSymbol::Initialize(void* p)
{
	random_device seed;
	default_random_engine dre(seed());
	uniform_int_distribution<int> randomLevel(1, 20);

	m_symbolLevel = randomLevel(dre);

	CalculateArcaneForce();

	return true;
}

void ArcaneSymbol::Update()
{
}

void ArcaneSymbol::CalculateArcaneForce()
{
	// 아케인포스 레벨별 수치 : arcaneForce = 30 + (level - 1) * 10
	m_arcaneForce = 30 + (m_symbolLevel - 1) * 10;

	//심볼 레벨업 필요 수치 : 현재 심볼 레벨수의 제곱 +11
	m_levelUpNeeds = m_symbolLevel * m_symbolLevel + 11;
}

