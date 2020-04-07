#include "Camera.h"
#include "../GameObject/GameObject.h"

INIT_INSTACNE(Camera)
Camera::Camera()
{
	m_target = nullptr;

	m_viewMatrix = Matrix3x2F::Identity();

	m_rightVector = VECTOR2D(1.0f, 0.0f);
	m_upVector = VECTOR2D(0.0f, 1.0f);
	m_positionVector = VECTOR2D(0.0f, 0.0f);

	m_angle = 0.0f;

	m_viewport = { 0 };

	m_extents = VECTOR2D(0.0f, 0.0f);
}

Camera::~Camera()
{
}

bool Camera::Initialize()
{
	m_extents = VECTOR2D(static_cast<float>(FRAME_BUFFER_WIDTH), static_cast<float>(FRAME_BUFFER_HEIGHT));
	m_positionVector -= 0.5f * m_extents;

	m_viewport.m_xStart = 0;
	m_viewport.m_yStart = 0;
	m_viewport.m_nWidth = FRAME_BUFFER_WIDTH;
	m_viewport.m_nHeight = FRAME_BUFFER_HEIGHT;
	m_viewport.m_nMinLayer = 0;
	m_viewport.m_nMaxLayer = 1;

	RegenerateViewMatrix();

	return true;
}

void Camera::Move(VECTOR2D & vShift)
{
	m_positionVector += vShift; 
}

void Camera::Rotate(float delta)
{
	if (!::IsZero(delta))
	{
		m_angle += delta;
		Matrix3x2F d2dmtxRotate;
		d2dmtxRotate = Matrix3x2F::Rotation(delta, Point2F(0.0f, 0.0f));
		m_rightVector = m_rightVector.Transform(&d2dmtxRotate);
		m_rightVector = m_rightVector.Normalize();
		m_upVector = m_upVector.Transform(&d2dmtxRotate);
		m_upVector = m_upVector.Normalize();
	}
}

void Camera::Update(float elapsedTime)
{

	RegenerateViewMatrix();
}

void Camera::RegenerateViewMatrix()
{
	m_viewMatrix._11 = m_rightVector.x;
	m_viewMatrix._21 = m_rightVector.y;

	m_viewMatrix._12 = m_upVector.x;
	m_viewMatrix._22 = m_upVector.y;

	m_viewMatrix._31 = -(m_positionVector * m_rightVector);
	m_viewMatrix._32 = -(m_positionVector * m_upVector);
}

bool Camera::IsVisible(GameObject* object)
{
	if (object->GetCollider() != nullptr)
	{
		AABB rcCamera(m_positionVector, m_extents);
		switch (object->GetCollider()->GetType())
		{
		case COLLIDER_AABB:
			{
				AABBCollider* aabbCollider = reinterpret_cast<AABBCollider*>(object->GetCollider());
				aabbCollider->Update(&object->GetWorldMatrix());
				AABB rcAABB = aabbCollider->GetTransformedBounds(&object->GetWorldMatrix(), nullptr);
				return(rcCamera.Intersect(&rcAABB));
			}

		case COLLIDER_OOBB:
			{
				OOBBCollider* oobbCollider = reinterpret_cast<OOBBCollider*>(object->GetCollider());
				OOBB rcOOBB = oobbCollider->GetTransformedBounds(&object->GetWorldMatrix());
				return rcCamera.Intersect(&rcOOBB);
			}

		case COLLIDER_CIRCLE:
			{
				CircleCollider* circleCollider = reinterpret_cast<CircleCollider*>(object->GetCollider());
				CIRCLE ccCircle = circleCollider->GetTransformedBounds(&object->GetWorldMatrix());
				return rcCamera.Intersect(&ccCircle);
			}
		}
	}

	return true;
}

void Camera::SetViewport(UINT xStart, UINT yStart, UINT nWidth, UINT nHeight, UINT nMinLayer, UINT nMaxLayer)
{
	m_viewport.m_xStart = xStart;
	m_viewport.m_yStart = yStart;
	m_viewport.m_nWidth = nWidth;
	m_viewport.m_nHeight = nHeight;
	m_viewport.m_nMinLayer = nMinLayer;
	m_viewport.m_nMaxLayer = nMaxLayer;
}