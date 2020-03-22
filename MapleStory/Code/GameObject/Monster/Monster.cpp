#include "Monster.h"
#include "../../D2DManager/D2DManager.h"

Monster::Monster()
	: GameObject(), m_PrevAnimation(0), m_AnimationName(""), m_Frame(0.f)
{
	m_AnimationMap.clear();
}

Monster::~Monster()
{
	m_AnimationMap.clear();

	cout << "Monster - ¼Ò¸êÀÚ" << endl;
}

bool Monster::Initialize()
{
	if (GET_INSTANCE(D2DManager)->CreateTexture("Idle", ImageInfo(L"../Resource/Textures/Character/Pinkbin_Idle.png", 720, 120, ANIMATION_FRAME::IDLE_FRAME, 1, 0, 0, 150, 150)) == false)

		return false;
	m_AnimationMap.emplace(ANIMATION::IDLE, ANIMATION_FRAME::IDLE_FRAME);

	if (GET_INSTANCE(D2DManager)->CreateTexture("Break", ImageInfo(L"../Resource/Textures/Character/Pinkbin_Break.png", 3770, 130, ANIMATION_FRAME::BREAK_FRAME, 1, 0, 0, 150, 150)) == false)
		return false;

	m_AnimationMap.emplace(ANIMATION::BREAK, ANIMATION_FRAME::BREAK_FRAME);

	if (GET_INSTANCE(D2DManager)->CreateTexture("Die", ImageInfo(L"../Resource/Textures/Character/Pinkbin_Die.png", 9570, 105, ANIMATION_FRAME::DIE_FRAME, 1, 0, 0, 150, 150)) == false)
		return false;

	if (GET_INSTANCE(D2DManager)->CreateTexture("Coin", ImageInfo(L"../Resource/Textures/coin/export/coin.png", 1024, 1024, ANIMATION_FRAME::DIE_FRAME, 1, 0, 0, 305, 302)) == false)
		return false;

	m_Frame = 0.f;
	m_PrevAnimation = ANIMATION::BREAK;
	m_AnimationName = "Break";

	return true;
}

void Monster::Update(float elapsedTime)
{
	auto iter = m_AnimationMap.find(static_cast<ANIMATION>(m_PrevAnimation));
	if (iter == m_AnimationMap.end())
		return;

	m_Frame += elapsedTime * 5;
	if (m_Frame > (*iter).second)
		m_Frame = 0.f;
}

void Monster::Render()
{
	GET_INSTANCE(D2DManager)->Render(m_AnimationName, m_WorldPosition, static_cast<int>(m_Frame), 0);
	GET_INSTANCE(D2DManager)->Render("Coin", m_WorldPosition, 0, 0);
}

void Monster::Release()
{
}
