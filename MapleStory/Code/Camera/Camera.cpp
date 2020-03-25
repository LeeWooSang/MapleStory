#include "Camera.h"
#include "../GameObject/GameObject.h"

INIT_INSTACNE(Camera)
Camera::Camera()
{
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

void Camera::SetViewport(UINT xStart, UINT yStart, UINT nWidth, UINT nHeight, UINT nMinLayer, UINT nMaxLayer)
{
	m_viewport.m_xStart = xStart;
	m_viewport.m_yStart = yStart;
	m_viewport.m_nWidth = nWidth;
	m_viewport.m_nHeight = nHeight;
	m_viewport.m_nMinLayer = nMinLayer;
	m_viewport.m_nMaxLayer = nMaxLayer;
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
}

bool Camera::IsVisible(GameObject* pGameObject)
{
	//if (pGameObject->m_pCollider)
	//{
	//	AABB rCamera(m_vPosition, m_vExtents);
	//	switch (pGameObject->m_pCollider->GetType())
	//	{
	//	case COLLIDER_AABB:
	//	{
	//		CAABBCollider *pAABBCollider = (CAABBCollider *)pGameObject->m_pCollider;
	//		pAABBCollider->Update(&pGameObject->m_d2dmtxWorld);
	//		AABB rcAABB = pAABBCollider->GetTransformedBounds(&pGameObject->m_d2dmtxWorld, NULL);
	//		return(rCamera.Intersect(&rcAABB));
	//	}
	//	case COLLIDER_OOBB:
	//	{
	//		COOBBCollider *pOOBBCollider = (COOBBCollider *)pGameObject->m_pCollider;
	//		OOBB rcOOBB = pOOBBCollider->GetTransformedBounds(&pGameObject->m_d2dmtxWorld);
	//		return(rCamera.Intersect(&rcOOBB));
	//	}
	//	case COLLIDER_CIRCLE:
	//	{
	//		CCircleCollider *pCircleCollider = (CCircleCollider *)pGameObject->m_pCollider;
	//		CIRCLE ccCircle = pCircleCollider->GetTransformedBounds(&pGameObject->m_d2dmtxWorld);
	//		return(rCamera.Intersect(&ccCircle));
	//	}
	//	}
	//}

	return true;
}
