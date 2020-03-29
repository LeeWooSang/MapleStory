#include "Player.h"
#include "../../../Camera/Camera.h"
#include "../../../../../GameServer/Code/Protocol.h"

Player::Player(const string& name) 
	: Character(name)
{
	m_positionVector = VECTOR2D(0.0f, 0.0f);
	m_rightVector = VECTOR2D(1.0f, 0.0f);
	m_upVector = VECTOR2D(0.0f, -1.0f);

	//m_rot = VECTOR2D(0.0f, 0.0f);
	//m_center = VECTOR2D(0.0f, 0.0f);

	m_pPlayerUpdatedContext = NULL;
	m_pCameraUpdatedContext = NULL;
}

Player::~Player()
{
}

bool Player::Initialize()
{
	//if (GET_INSTANCE(D2DManager)->CreateTexture("Action", ImageInfo(L"../Resource/Textures/Character/Action.png", 900, 100, ANIMATION_FRAME::ACTION_FRAME, 1, 0, 0, 150, 150)) == false)
	//	return false;

	//m_AnimationMap.emplace(ANIMATION::ACTION, ANIMATION_FRAME::ACTION_FRAME);

	//if (GET_INSTANCE(D2DManager)->CreateTexture("RagingBlow", ImageInfo(L"../Resource/Textures/Skill/Effect/RagingBlow.png", 5850, 380, ANIMATION_FRAME::RAGINGBLOW_FRAME, 1, 0, 0, 380, 380)) == false)
	//	return false;

	if (GameObject::Initialize() == false)
		return false;

	m_friction = 50.f;
	m_gravity = VECTOR2D(0.f, 0.f);
	m_maxVelocity = VECTOR2D(125.f, 125.f);
	m_positionVector = VECTOR2D(0.f, 0.f);
	RegenerateWorldMatrix();

	return true;
}

void Player::Update(float elapsedTime)
{
	Move(elapsedTime);

	m_velocity += m_gravity * elapsedTime;
	float length = m_velocity.Length();
	if (!::IsZero(length))
	{
		if (m_velocity.x > m_maxVelocity.x)
			m_velocity.x *= (m_maxVelocity.x / length);

		if (m_velocity.y > m_maxVelocity.y)
			m_velocity.y *= (m_maxVelocity.y / length);

		Move(m_velocity * elapsedTime, false);

		//if (m_pPlayerUpdatedContext) 
		//	OnPlayerUpdated(elapsedTime);
	}

	GET_INSTANCE(Camera)->Update(elapsedTime);

	//if (m_pCameraUpdatedContext) 
	//	OnCameraUpdated(elapsedTime);


	if (!::IsZero(m_friction))
	{
		VECTOR2D vDeceleration = -m_velocity;
		vDeceleration = vDeceleration.Normalize();
		length = m_velocity.Length();

		float fDeceleration = (m_friction * elapsedTime);

		if (fDeceleration > length) 
			fDeceleration = length;

		m_velocity += vDeceleration * fDeceleration;
	}
}

void Player::Render()
{
	GameObject::Render();
}

void Player::RegenerateWorldMatrix()
{
	m_worldMatrix._11 = m_rightVector.x; 
	m_worldMatrix._12 = m_rightVector.y;

	m_worldMatrix._21 = m_upVector.x;
	m_worldMatrix._22 = m_upVector.y;

	m_worldMatrix._31 = m_positionVector.x; 
	m_worldMatrix._32 = m_positionVector.y;
}

void Player::Move(float elapsedTime)
{
	char dir = 0;
	float distance = elapsedTime * 100;

	VECTOR2D shift = VECTOR2D(0.f, 0.f);

	if (KEY_DOWN(VK_RIGHT))
	{
		dir |= DIR_TYPE::RIGHT;
		shift += m_rightVector * distance;
	}

	if (KEY_DOWN(VK_LEFT))
	{
		dir |= DIR_TYPE::LEFT;
		shift -= m_rightVector * distance;
	}

	if (KEY_DOWN(VK_UP))
	{
		dir |= DIR_TYPE::UP;
		shift += m_upVector * distance;
	}

	if (KEY_DOWN(VK_DOWN))
	{
		dir |= DIR_TYPE::DOWN;
		shift -= m_upVector * distance;
	}

	if(dir)
		Move(shift, true);
}

//void Player::Move(char direction, VECTO distance, bool velocity)
//{
//}

void Player::Move(VECTOR2D& shift, bool updateVelocity)
{
	if (updateVelocity == true)
		m_velocity += shift;

	else
	{
		m_positionVector += shift;
		RegenerateWorldMatrix();

		GET_INSTANCE(Camera)->Move(shift);

	}
}
