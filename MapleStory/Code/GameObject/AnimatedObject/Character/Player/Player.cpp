#include "Player.h"
#include "../../../../ResourceManager/ResourceManager.h"
#include "../../../../Camera/Camera.h"
#include "../../../../../../GameServer/Code/Protocol.h"
#include "../../../../Animation/Animation.h"
#include "../../../../Input/Input.h"

Player::Player(const string& name) 
	: Character(name)
{
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
	unordered_multimap<string, AnimatedObjectInfo*>infoList = GET_INSTANCE(ResourceManager)->GetCharacterObjectInfoList();

	string objName = "Body";
	AnimatedObject* body = InitHierarchy(objName);	
	for (auto iter = infoList.lower_bound(objName); iter != infoList.upper_bound(objName); ++iter)
		InitAnimation((*iter).second->m_size, (*iter).second->m_animationName, (*iter).second->m_textureName, body);

	objName = "Arm";
	AnimatedObject* arm = InitHierarchy(objName);
	for (auto iter = infoList.lower_bound(objName); iter != infoList.upper_bound(objName); ++iter)
		InitAnimation((*iter).second->m_size, (*iter).second->m_animationName, (*iter).second->m_textureName, arm);

	objName = "Head";
	AnimatedObject* head = InitHierarchy(objName);
	for (auto iter = infoList.lower_bound(objName); iter != infoList.upper_bound(objName); ++iter)
		InitAnimation((*iter).second->m_size, (*iter).second->m_animationName, (*iter).second->m_textureName, head);

	SetAnimation("Idle");
	RegenerateColliderAABB();

	m_friction = 50.f;
	m_gravity = VECTOR2D(0.f, GRAVITY);
	m_maxVelocity = VECTOR2D(125.f, 125.f);

	m_worldMatrix._21 = 0.f;
	m_worldMatrix._22 = -1.f;

	RegenerateWorldMatrix();

	return true;
}

void Player::Update(float elapsedTime)
{
	m_velocity += m_gravity * elapsedTime * 100;
	if (m_collisionObject != nullptr)
		m_velocity.y = 0.f;

	Move(elapsedTime);
	ProcessInput();

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

	//if (!::IsZero(m_friction))
	//{
	//	VECTOR2D vDeceleration = -m_velocity;
	//	vDeceleration = vDeceleration.Normalize();
	//	length = m_velocity.Length();

	//	float fDeceleration = (m_friction * elapsedTime);

	//	if (fDeceleration > length || m_collision == true) 
	//		fDeceleration = length;

	//	m_velocity += vDeceleration * fDeceleration;
	//}

	Character::Update(elapsedTime);
	cout << m_worldMatrix._31 << ", " << m_worldMatrix._32 << endl;
}

void Player::Render()
{
	Character::Render();
}

void Player::RegenerateWorldMatrix()
{
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
	VECTOR2D temp = VECTOR2D(0.f, 0.f);

	if (KEY_DOWN(VK_RIGHT))
	{
		dir |= DIR_TYPE::RIGHT;
		temp = VECTOR2D(m_worldMatrix._11, m_worldMatrix._12);
		shift += temp * distance;
	}

	if (KEY_DOWN(VK_LEFT))
	{
		dir |= DIR_TYPE::LEFT;
		temp = VECTOR2D(m_worldMatrix._11, m_worldMatrix._12);
		shift -= temp * distance;
	}

	if (KEY_DOWN(VK_MENU))
	{
		dir |= DIR_TYPE::UP;
		temp = VECTOR2D(m_worldMatrix._21, m_worldMatrix._22);
		shift += temp * distance * 30;
	}

	if (KEY_DOWN(VK_DOWN))
	{
		dir |= DIR_TYPE::DOWN;
		temp = VECTOR2D(m_worldMatrix._21, m_worldMatrix._22);
		shift -= temp * distance;
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
		VECTOR2D pos = VECTOR2D(m_worldMatrix._31 + shift.x, m_worldMatrix._32 + shift.y);
		SetPosition(pos);
		GET_INSTANCE(Camera)->Move(shift);
	}
}

void Player::ProcessInput()
{
	GET_INSTANCE(Input)->ProcessKeyEvent();

	if (GET_INSTANCE(Input)->GetIsPushed(KEY_TYPE::KEYBOARD_LEFT) == true)
	{
		cout << "첨 누름" << endl;
		SetDirection(1);
		SetAnimation("Walk");
		// 이때 다른 플레이어에게 애니메이션 정보를 보내면 됨
	}

	else if (GET_INSTANCE(Input)->GetIsPushed(KEY_TYPE::KEYBOARD_RIGHT) == true)
	{
		cout << "첨 누름" << endl;
		SetDirection(-1);
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
