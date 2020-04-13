#include "Player.h"
#include "../../../Camera/Camera.h"
#include "../../../../../GameServer/Code/Protocol.h"
#include "../../../Animation/Animation.h"
#include "../../../Input/Input.h"

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
	InitAnimation();
	m_animation = "Idle";
	SetAnimation(m_animation);
	RegenerateColliderAABB();

	m_friction = 50.f;
	m_gravity = VECTOR2D(0.f, GRAVITY);
	m_maxVelocity = VECTOR2D(125.f, 125.f);
	m_positionVector = VECTOR2D(0.f, 0.f);
	RegenerateWorldMatrix();

	return true;
}

void Player::Update(float elapsedTime)
{
	ProcessInput();

	Move(elapsedTime);

	m_velocity += m_gravity * elapsedTime * 100;
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

	Character::Update(elapsedTime);
	//cout << m_worldMatrix._31 << ", " << m_worldMatrix._32 << endl;
}

void Player::Render()
{
	Character::Render();
}

void Player::InitAnimation()
{
	string objectName;

	{
		objectName = "Body";
		Character* body = new Character(objectName);
		//m_hierarchyMap.emplace(objectName, body);
		m_hierarchyList.emplace_back(body);
		body->SetRightVector(VECTOR2D(1.f, 0.f));
		body->SetUpVector(VECTOR2D(0.f, -1.f));

		Animation* IdleBodyAni = new Animation("Idle");
		IdleBodyAni->AddAnimation("IdleBody0");
		IdleBodyAni->AddAnimation("IdleBody1");
		IdleBodyAni->AddAnimation("IdleBody2");
		body->AddAnimation("Idle", IdleBodyAni);

		Animation* walkBodyAni = new Animation("Walk");
		walkBodyAni->AddAnimation("WalkBody0");
		walkBodyAni->AddAnimation("WalkBody1");
		walkBodyAni->AddAnimation("WalkBody2");
		walkBodyAni->AddAnimation("WalkBody3");
		body->AddAnimation("Walk", walkBodyAni);

		Animation* jumpBodyAni = new Animation("Jump");
		jumpBodyAni->AddAnimation("JumpBody0");
		body->AddAnimation("Jump", jumpBodyAni);
	}

	{
		objectName = "Arm";
		Character* arm = new Character(objectName);
		//m_hierarchyMap.emplace(objectName, arm);
		m_hierarchyList.emplace_back(arm);
		arm->SetRightVector(VECTOR2D(1.f, 0.f));
		arm->SetUpVector(VECTOR2D(0.f, -1.f));

		Animation* IdleArmAni = new Animation("Idle");
		IdleArmAni->AddAnimation("IdleArm0");
		IdleArmAni->AddAnimation("IdleArm1");
		IdleArmAni->AddAnimation("IdleArm2");
		arm->AddAnimation("Idle", IdleArmAni);

		Animation* walkArmAni = new Animation("Walk");
		walkArmAni->AddAnimation("WalkArm0");
		walkArmAni->AddAnimation("WalkArm1");
		walkArmAni->AddAnimation("WalkArm2");
		walkArmAni->AddAnimation("WalkArm3");
		arm->AddAnimation("Walk", walkArmAni);

		Animation* jumpArmAni = new Animation("Jump");
		jumpArmAni->AddAnimation("JumpArm0");
		arm->AddAnimation("Jump", jumpArmAni);
	}

	{
		objectName = "Head";
		Character* head = new Character(objectName);
		head->SetRightVector(VECTOR2D(1.f, 0.f));
		head->SetUpVector(VECTOR2D(0.f, -1.f));
		m_hierarchyList.emplace_back(head);

		Animation* idleHeadAni = new Animation("Idle");
		idleHeadAni->AddAnimation("FrontHead");
		head->AddAnimation("Idle", idleHeadAni);

		Animation* walkHeadAni = new Animation("Walk");
		walkHeadAni->AddAnimation("FrontHead");
		head->AddAnimation("Walk", walkHeadAni);

		Animation* jumpHeadAni = new Animation("Jump");
		jumpHeadAni->AddAnimation("FrontHead");
		head->AddAnimation("Jump", jumpHeadAni);
	}
}

void Player::RegenerateWorldMatrix()
{
	m_worldMatrix._11 = m_rightVector.x; 
	m_worldMatrix._12 = m_rightVector.y;

	m_worldMatrix._21 = m_upVector.x;
	m_worldMatrix._22 = m_upVector.y;

	m_worldMatrix._31 = m_positionVector.x; 
	m_worldMatrix._32 = m_positionVector.y;

	for (auto& object : m_hierarchyList)
	{
		object->SetRightVector(VECTOR2D(m_worldMatrix._11, m_worldMatrix._12));
		object->SetUpVector(VECTOR2D(m_worldMatrix._21, m_worldMatrix._22));
		object->SetPosition(VECTOR2D(m_worldMatrix._31, m_worldMatrix._32));
	}
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

	if (dir)
	{
		/*if (dir & DIR_TYPE::LEFT)
		{
			float minWidth = -WORLD_WIDTH * 0.5f;
			if (m_positionVector.x <= minWidth)
			{
				m_positionVector.x = minWidth;
				RegenerateWorldMatrix();
				return;
			}

		}
		else if (dir & DIR_TYPE::RIGHT)
		{
			float maxWidth = WORLD_WIDTH * 0.5f;
			if (m_positionVector.x >= maxWidth)
			{
				m_positionVector.x = maxWidth;
				RegenerateWorldMatrix();
				return;
			}

		}*/
			
		Move(shift, true);
	}

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

void Player::ProcessInput()
{
	GET_INSTANCE(Input)->ProcessKeyEvent();

	if (GET_INSTANCE(Input)->GetIsPushed(KEY_TYPE::KEYBOARD_LEFT) == true
		|| GET_INSTANCE(Input)->GetIsPushed(KEY_TYPE::KEYBOARD_RIGHT) == true)
	{
		cout << "첨 누름" << endl;
		SetAnimation("Walk");
		// 이때 다른 플레이어에게 애니메이션 정보를 보내면 됨
	}
	else if (GET_INSTANCE(Input)->GetIsPushed(KEY_TYPE::KEYBOARD_ALT) == true)
	{
		cout << "점프 누름" << endl;
		SetAnimation("Jump");
	}

	if (GET_INSTANCE(Input)->GetIsPop(KEY_TYPE::KEYBOARD_LEFT) == true
		|| GET_INSTANCE(Input)->GetIsPop(KEY_TYPE::KEYBOARD_RIGHT) == true
		|| GET_INSTANCE(Input)->GetIsPop(KEY_TYPE::KEYBOARD_ALT) == true)
	{		
		cout << "첨 땜" << endl;
		SetAnimation("Idle");
		// 이때 다른 플레이어에게 애니메이션 정보를 보내면 됨
	}

	if (KEY_DOWN(VK_ESCAPE))
		PostQuitMessage(0);
}
