#include "Player.h"
#include "../../../Camera/Camera.h"

Player::Player(const string& name) 
	: Character(name)
{
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

	return true;
}

void Player::Update(float elapsedTime)
{
	m_velocity += m_gravity * elapsedTime;
	float length = m_velocity.Length();
	if (!::IsZero(length))
	{
		if (m_velocity.x > m_vMaxVelocity.x)
			m_velocity.x *= (m_vMaxVelocity.x / length);

		if (m_velocity.y > m_vMaxVelocity.y)
			m_velocity.y *= (m_vMaxVelocity.y / length);

		Move(m_velocity * elapsedTime, false);

		//if (m_pPlayerUpdatedContext) 
		//	OnPlayerUpdated(elapsedTime);
	}

	if (m_camera) 
		m_camera->Update(elapsedTime);

	//if (m_pCameraUpdatedContext) 
	//	OnCameraUpdated(elapsedTime);

	m_camera->RegenerateViewMatrix();

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
	Matrix3x2F transform = m_worldMatrix;
	transform = transform * GET_INSTANCE(Camera)->GetViewMatrix();
	GET_INSTANCE(D2DManager)->GetRenderTarget()->SetTransform(transform);

	D2D1_RECT_F rect;
	m_collider->GetAABB(&rect);

	//GET_INSTANCE(D2DManager)->GetRenderTarget()->DrawBitmap(m_pd2dBitmap, rect);

	//if (m_pd2dGeometry && m_pd2dsbrFill)
	//	pd2dRenderTarget->FillGeometry(m_pd2dGeometry, m_pd2dsbrFill);
	//if (m_pd2dGeometry && m_pd2dsbrDraw)
	//	pd2dRenderTarget->DrawGeometry(m_pd2dGeometry, m_pd2dsbrDraw);
	//
	if (m_isDrawBoundingBox == true && m_collider != nullptr)
	{
		switch (m_collider->GetType())
		{
			case COLLIDER_AABB:
			{
				D2D1_RECT_F d2drcBounds;
				CAABBCollider *pAABBCollider = reinterpret_cast<CAABBCollider*>(m_collider);
				//				pAABBCollider->GetBounds(&d2drcBounds);
				pAABBCollider->GetTransformedBounds(&m_worldMatrix, &d2drcBounds);

				if (m_camera != nullptr)
					GET_INSTANCE(D2DManager)->GetRenderTarget()->SetTransform(m_camera->GetViewMatrix());
				else
					GET_INSTANCE(D2DManager)->GetRenderTarget()->SetTransform(Matrix3x2F::Identity());

				//pd2dRenderTarget->DrawRectangle(d2drcBounds, m_pd2dsbrBounds);
				break;
			}

		case COLLIDER_OOBB:
			{
				D2D1_RECT_F boundRect;
				COOBBCollider *pOOBBCollider = reinterpret_cast<COOBBCollider*>(m_collider);
				pOOBBCollider->GetBounds(&boundRect);
				//				pAABBCollider->GetTransformedBounds(&m_d2dmtxWorld, &d2drcBounds);
				//				pd2dRenderTarget->SetTransform((pCamera) ? pCamera->m_d2dmtxView : Matrix3x2F::Identity());
				//pd2dRenderTarget->DrawRectangle(d2drcBounds, m_pd2dsbrBounds);
				break;
			}

		case COLLIDER_CIRCLE:
			{
				CCircleCollider *pCircleCollider = reinterpret_cast<CCircleCollider*>(m_collider);
				//				CIRCLE ccCircle = pCircleCollider->GetTransformedBounds(&m_d2dmtxWorld);
				//				D2D1_ELLIPSE d2dEllipse = Ellipse(ccCircle.m_vCenter, ccCircle.m_fRadius, ccCircle.m_fRadius);
				D2D1_ELLIPSE d2dEllipse;
				pCircleCollider->GetBounds(&d2dEllipse);
				//				pd2dRenderTarget->SetTransform((pCamera) ? pCamera->m_d2dmtxView : Matrix3x2F::Identity());
				//pd2dRenderTarget->DrawEllipse(d2dEllipse, m_pd2dsbrBounds);
				break;
			}
		}
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
}

void Player::Move(VECTOR2D& shift, bool updateVelocity)
{
	if (updateVelocity == true)
		m_velocity += shift;

	else
	{
		m_positionVector += shift;
		RegenerateWorldMatrix();
		m_camera->Move(shift);
	}
}
