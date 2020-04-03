#include "GameObject.h"
#include "../ResourceManager/ResourceManager.h"
#include "../ResourceManager/Texture/Texture.h"
#include "../Camera/Camera.h"

GameObject::GameObject(const string& name)
	: m_name(name)
{
	m_worldMatrix = Matrix3x2F::Identity();
	m_collider = nullptr;
	m_angle = 0;
	m_velocity = VECTOR2D(0.f, 0.f);
	m_maxVelocity = VECTOR2D(0.f, 0.f);
	m_gravity = VECTOR2D(0.f, 0.f);
	m_isDrawBoundingBox = false;

	//m_animationName.clear();
}

GameObject::~GameObject()
{
	if (m_collider)
		delete m_collider;

	SAFE_DELETE_VECTOR(m_hierarchyList);
}

bool GameObject::Initialize()
{
	//m_animationName = m_name;

	Texture* tex = GET_INSTANCE(ResourceManager)->GetTexture(m_name);
	if (tex == nullptr)
		return false;

	int width = tex->GetWidth();
	int height = tex->GetHeight();
	m_collider = new AABBCollider(AABB(-width * 0.5f, -height * 0.5f, width * 0.5f, height * 0.5f));

	m_isDrawBoundingBox = true;

	return true;
}

void GameObject::Render()
{
	//Texture* tex = GET_INSTANCE(ResourceManager)->GetTexture(m_name);
	Texture* tex = GET_INSTANCE(ResourceManager)->GetTexture(m_name);
	if (tex == nullptr)
		return;

	Matrix3x2F transform = m_worldMatrix;
	transform = transform * GET_INSTANCE(Camera)->GetViewMatrix();
	GET_INSTANCE(D2DManager)->GetRenderTarget()->SetTransform(transform);

	D2D1_RECT_F rect;
	m_collider->GetAABB(&rect);
	GET_INSTANCE(D2DManager)->GetRenderTarget()->DrawBitmap(tex->GetBitmap(), rect);
	RenderBoundingBox();
}

void GameObject::RenderBoundingBox()
{
	if (m_isDrawBoundingBox == true && m_collider != nullptr)
	{
		switch (m_collider->GetType())
		{
		case COLLIDER_AABB:
		{
			D2D1_RECT_F boundRect;
			AABBCollider* aabbCollider = reinterpret_cast<AABBCollider*>(m_collider);
			//				pAABBCollider->GetBounds(&d2drcBounds);
			aabbCollider->GetTransformedBounds(&m_worldMatrix, &boundRect);
			GET_INSTANCE(D2DManager)->GetRenderTarget()->SetTransform(GET_INSTANCE(Camera)->GetViewMatrix());
			GET_INSTANCE(D2DManager)->GetRenderTarget()->DrawRectangle(boundRect, GET_INSTANCE(D2DManager)->GetFontColor("說除儀"));
			break;
		}
		case COLLIDER_OOBB:
		{
			D2D1_RECT_F boundRect;
			OOBBCollider* oobbCollider = reinterpret_cast<OOBBCollider*>(m_collider);
			oobbCollider->GetBounds(&boundRect);
			oobbCollider->GetTransformedBounds(&m_worldMatrix);
			GET_INSTANCE(D2DManager)->GetRenderTarget()->SetTransform(GET_INSTANCE(Camera)->GetViewMatrix());
			GET_INSTANCE(D2DManager)->GetRenderTarget()->DrawRectangle(boundRect, GET_INSTANCE(D2DManager)->GetFontColor("說除儀"));
			break;
		}
		case COLLIDER_CIRCLE:
		{
			CircleCollider* circleCollider = reinterpret_cast<CircleCollider*>(m_collider);
			//				CIRCLE ccCircle = pCircleCollider->GetTransformedBounds(&m_d2dmtxWorld);
			//				D2D1_ELLIPSE d2dEllipse = Ellipse(ccCircle.m_vCenter, ccCircle.m_fRadius, ccCircle.m_fRadius);
			D2D1_ELLIPSE ellipse;
			circleCollider->GetBounds(&ellipse);
			//				pd2dRenderTarget->SetTransform((pCamera) ? pCamera->m_d2dmtxView : Matrix3x2F::Identity());
			GET_INSTANCE(D2DManager)->GetRenderTarget()->DrawEllipse(ellipse, GET_INSTANCE(D2DManager)->GetFontColor("說除儀"));
			break;
		}
		}
	}
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