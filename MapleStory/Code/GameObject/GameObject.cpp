#include "GameObject.h"

GameObject::GameObject(const string& name)
	: m_name(name)
{
	m_worldMatrix = Matrix3x2F::Identity();
	m_isDrawBoundingBox = false;
}

GameObject::~GameObject()
{
	if (m_collider)
		delete m_collider;
}

VECTOR2D GameObject::GetRightVector() const
{
	VECTOR2D right = VECTOR2D(m_worldMatrix._11, m_worldMatrix._12);
	return right.Normalize();
}

void GameObject::SetRightVector(VECTOR2D right)
{
	m_worldMatrix._11 = right.x;
	m_worldMatrix._12 = right.y;
}

VECTOR2D GameObject::GetUpVector() const
{
	VECTOR2D up = VECTOR2D(m_worldMatrix._21, m_worldMatrix._22);
	return up.Normalize();
}

void GameObject::SetUpVector(VECTOR2D up)
{
	m_worldMatrix._21 = up.x;
	m_worldMatrix._22 = up.y;
}

VECTOR2D GameObject::GetPositionVector() const
{
	return VECTOR2D(m_worldMatrix._31, m_worldMatrix._32);
}

void GameObject::SetPosition(VECTOR2D position)
{
	m_worldMatrix._31 = position.x;
	m_worldMatrix._32 = position.y;
}

VECTOR2D GameObject::GetSize(Matrix3x2F* pd2dmtxTransform)
{
	if (pd2dmtxTransform != nullptr)
		return m_collider->GetSize(pd2dmtxTransform);

	return m_collider->GetSize(&m_worldMatrix);
}

