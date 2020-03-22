#include "Player.h"
#include"../../D2DManager/D2DManager.h"
#include "../../Network/Network.h"
#include "../../Camera/Camera.h"

Player::Player() 
	: GameObject(), m_PrevAnimation(0), m_AnimationName(""), m_Frame(0.f)
{
	m_ActionFrame = 0.f;
	m_AnimationMap.clear();
}

Player::~Player()
{
	m_AnimationMap.clear();

	cout << "Player - ¼Ò¸êÀÚ" << endl;
}

bool Player::Initialize()
{
	if (GET_INSTANCE(D2DManager)->CreateTexture("Action", ImageInfo(L"../Resource/Textures/Character/Action.png", 900, 100, ANIMATION_FRAME::ACTION_FRAME, 1, 0, 0, 150, 150)) == false)
		return false;

	m_AnimationMap.emplace(ANIMATION::ACTION, ANIMATION_FRAME::ACTION_FRAME);

	if (GET_INSTANCE(D2DManager)->CreateTexture("RagingBlow", ImageInfo(L"../Resource/Textures/Skill/Effect/RagingBlow.png", 5850, 380, ANIMATION_FRAME::RAGINGBLOW_FRAME, 1, 0, 0, 380, 380)) == false)
		return false;

	m_AnimationMap.emplace(ANIMATION::RAGINGBLOW, ANIMATION_FRAME::RAGINGBLOW_FRAME);

	//m_Frame = ANIMATION_FRAME::IDLE_FRAME;
	//m_PrevAnimation = ANIMATION::IDLE;
	//m_AnimationName = "Idle";

	m_PrevAnimation = ANIMATION::RAGINGBLOW;
	m_Frame = 0.f;
	m_ActionFrame = 0.f;
	m_AnimationName = "RagingBlow";
	m_Speed = 0.5f;

	GET_INSTANCE(Camera)->SetTarget(this);

	return true;
}

void Player::Update(float elapsedTime)
{
	float moveSize = m_Speed * elapsedTime;

	char dir = DIRECTION::IDLE;
	//char animation = ANIMATION::IDLE;
	char animation = ANIMATION::RAGINGBLOW;

	float gap = 0.9f;
	
	XMFLOAT2 pos = m_WorldPosition;

	if (GetAsyncKeyState(VK_UP) & 0x8000)
	{
		dir |= DIRECTION::UP;
		m_WorldPosition.y += moveSize;
		if (m_WorldPosition.y >= gap)
			m_WorldPosition.y = gap;

		//GET_INSTANCE(Camera)->SetWorldPosition(XMFLOAT2(cameraPos.x, cameraPos.y - moveSize));
	}

	else if (GetAsyncKeyState(VK_DOWN) & 0x8000)
	{
		dir |= DIRECTION::DOWN;
		m_WorldPosition.y -= moveSize;
		if (m_WorldPosition.y <= -gap)
			m_WorldPosition.y = -gap;

		//GET_INSTANCE(Camera)->SetWorldPosition(XMFLOAT2(cameraPos.x, cameraPos.y + moveSize));
	}

	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		dir |= DIRECTION::RIGHT;

		m_WorldPosition.x += moveSize;
		if (m_WorldPosition.x >= gap)
			m_WorldPosition.x = gap;

		//GET_INSTANCE(Camera)->SetWorldPosition(XMFLOAT2(cameraPos.x - moveSize, cameraPos.y));
	}

	else if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		dir |= DIRECTION::LEFT;

		m_WorldPosition.x -= moveSize;
		if (m_WorldPosition.x <= -gap)
			m_WorldPosition.x = -gap;

		//GET_INSTANCE(Camera)->SetWorldPosition(XMFLOAT2(cameraPos.x + moveSize, cameraPos.y));
	}
	
	if (GetAsyncKeyState(VK_CONTROL) & 0x8000)
	{
		animation |= ANIMATION::IDLE;
	}

	GET_INSTANCE(Camera)->Update(dir, moveSize);

	if (dir != DIRECTION::IDLE)
	{
		//GET_INSTANCE(Network)->Send_Move_Packet(dir);
	}

	ProcessAnimation(animation, elapsedTime);
}

void Player::Render()
{
	D2D1_POINT_2F center = D2D1::Point2F(FRAME_BUFFER_WIDTH * 0.5, FRAME_BUFFER_HEIGHT * 0.5f);

	D2D1::Matrix3x2F symmetryMatrix = D2D1::Matrix3x2F::Scale(-1, 1, center);
	GET_INSTANCE(D2DManager)->GetRenderTarget()->SetTransform(symmetryMatrix);

	GET_INSTANCE(D2DManager)->Render("Action", m_WorldPosition, static_cast<int>(m_ActionFrame), 0);
	GET_INSTANCE(D2DManager)->Render(m_AnimationName, m_WorldPosition, static_cast<int>(m_Frame), 0);

	//cout << m_WorldPosition.x << ", " << m_WorldPosition.y << endl;

	symmetryMatrix = D2D1::Matrix3x2F::Scale(1, 1, center);
	GET_INSTANCE(D2DManager)->GetRenderTarget()->SetTransform(symmetryMatrix);
}

void Player::Release()
{
}

void Player::ProcessAnimation(char animation, float elapsedTime)
{
	auto iter = m_AnimationMap.find(static_cast<ANIMATION>(animation));
	if (iter == m_AnimationMap.end())
		return;
	
	if (m_PrevAnimation != animation)
	{
		m_PrevAnimation = animation;

		switch (m_PrevAnimation)
		{
		case ANIMATION::IDLE:					m_AnimationName = "Idle";		break;
		case ANIMATION::RAGINGBLOW:	m_AnimationName = "RagingBlow";	break;
		default:	
			break;
		}

		m_Frame = 0.f;
	}

	m_Frame += elapsedTime * 20;
	if (m_Frame > (*iter).second)
		m_Frame = 0.f;

	if (m_PrevAnimation & ANIMATION::RAGINGBLOW)
	{
		if (m_Frame >= 10)
			m_ActionFrame = 8.f;

		else if (m_Frame >= 9)
			m_ActionFrame = 7.f;

		else if (m_Frame >= 8)
			m_ActionFrame = 6.f;

		else if (m_Frame >= 7)
			m_ActionFrame = 5.f;

		else if (m_Frame >= 6)
			m_ActionFrame = 4.f;

		else if (m_Frame >= 5)
			m_ActionFrame = 3.f;

		else if (m_Frame >= 3)
			m_ActionFrame = 2.f;

		else if (m_Frame >= 2)
			m_ActionFrame = 1.f;

		else
			m_ActionFrame = 0.f;
	}
}
