#include "Character.h"
#include "../../Animation/Animation.h"
#include "../../Camera/Camera.h"
#include "../../ResourceManager/ResourceManager.h"
#include "../../ResourceManager/Texture/Texture.h"

Character::Character(const string& name)
	: GameObject(name)
{
	m_animation.clear();
}

Character::~Character()
{
	SAFE_DELETE_MAP(m_animationMap);
}

bool Character::Initialize()
{
	return true;
}

void Character::Update(float elapsedTime)
{
	for (auto object : m_hierarchyList)
		object->Update(elapsedTime);

	// 현재 애니메이션에 해당하는 정보를 각 오브젝트마다 찾는다.
	auto iter = m_animationMap.find(m_animation);
	if (iter == m_animationMap.end())
		return;
	(*iter).second->Update(elapsedTime);

	RegenerateColliderAABB();
}

void Character::Render()
{
	for (auto object : m_hierarchyList)
		object->Render();

	auto iter = m_animationMap.find(m_animation);
	if (iter == m_animationMap.end())
		return;

	// 현재 재생할 애니메이션 이름을 얻어와 텍스쳐를 가져옴
	Texture* tex = GET_INSTANCE(ResourceManager)->GetTexture((*iter).second->GetAnimation());
	if (tex == nullptr)
		return;

	//int width = tex->GetWidth();
	//int height = tex->GetHeight();

	//if (m_collider == nullptr)
	//	m_collider = new AABBCollider(AABB(-width * 0.5f, -height * 0.5f, width * 0.5f, height * 0.5f));
	//else
	//	reinterpret_cast<AABBCollider*>(m_collider)->SetAABB(AABB(-width * 0.5f, -height * 0.5f, width * 0.5f, height * 0.5f));

	Matrix3x2F transform = m_worldMatrix;

	// 방향을 곱해줘야 함
	transform._11 *= m_direction;
	transform._31 += tex->GetOriginX() * m_direction;
	transform._32 += tex->GetOriginY();

	transform = transform * GET_INSTANCE(Camera)->GetViewMatrix();
	GET_INSTANCE(D2DManager)->GetRenderTarget()->SetTransform(transform);

	D2D1_RECT_F rect;
	m_collider->GetAABB(&rect);
	GET_INSTANCE(D2DManager)->GetRenderTarget()->DrawBitmap(tex->GetBitmap(), rect);

	Character::RenderBoundingBox();
}

void Character::RenderBoundingBox()
{
	if (m_isDrawBoundingBox == true && m_collider != nullptr)
	{
		auto iter = m_animationMap.find(m_animation);
		if (iter == m_animationMap.end())
			return;

		switch (m_collider->GetType())
		{
		case COLLIDER_AABB:
		{
			D2D1_RECT_F boundRect;
			AABBCollider* aabbCollider = reinterpret_cast<AABBCollider*>(m_collider);
			//				pAABBCollider->GetBounds(&d2drcBounds);

				// 현재 재생할 애니메이션 이름을 얻어와 텍스쳐를 가져옴
			Texture* tex = GET_INSTANCE(ResourceManager)->GetTexture((*iter).second->GetAnimation());
			if (tex == nullptr)
				return;

			int width = tex->GetWidth();
			int height = tex->GetHeight();

			Matrix3x2F transform = m_worldMatrix;

			transform._11 *= m_direction;
			transform._31 += tex->GetOriginX();
			transform._32 += tex->GetOriginY();

			aabbCollider->GetTransformedBounds(&transform, &boundRect);
			GET_INSTANCE(D2DManager)->GetRenderTarget()->SetTransform(GET_INSTANCE(Camera)->GetViewMatrix());
			GET_INSTANCE(D2DManager)->GetRenderTarget()->DrawRectangle(boundRect, GET_INSTANCE(D2DManager)->GetFontColor("빨간색"));
			break;
		}
		case COLLIDER_OOBB:
		{
			D2D1_RECT_F boundRect;
			OOBBCollider* oobbCollider = reinterpret_cast<OOBBCollider*>(m_collider);
			oobbCollider->GetBounds(&boundRect);
			oobbCollider->GetTransformedBounds(&m_worldMatrix);
			GET_INSTANCE(D2DManager)->GetRenderTarget()->SetTransform(GET_INSTANCE(Camera)->GetViewMatrix());
			GET_INSTANCE(D2DManager)->GetRenderTarget()->DrawRectangle(boundRect, GET_INSTANCE(D2DManager)->GetFontColor("빨간색"));
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
			GET_INSTANCE(D2DManager)->GetRenderTarget()->DrawEllipse(ellipse, GET_INSTANCE(D2DManager)->GetFontColor("빨간색"));
			break;
		}
		}
	}
}

bool Character::InitHierarchyMap()
{
	return true;
}

void Character::InitAnimation()
{
}

void Character::RegenerateColliderAABB()
{
	for (auto& object : m_hierarchyList)
		reinterpret_cast<Character*>(object)->RegenerateColliderAABB();

	auto iter = m_animationMap.find(m_animation);
	if (iter == m_animationMap.end())
		return;

	// 현재 재생할 애니메이션 이름을 얻어와 텍스쳐를 가져옴
	Texture* tex = GET_INSTANCE(ResourceManager)->GetTexture((*iter).second->GetAnimation());
	if (tex == nullptr)
		return;

	int width = tex->GetWidth();
	int height = tex->GetHeight();

	if (m_collider == nullptr)
		m_collider = new AABBCollider(AABB(-width * 0.5f, -height * 0.5f, width * 0.5f, height * 0.5f));
	else
		reinterpret_cast<AABBCollider*>(m_collider)->SetAABB(AABB(-width * 0.5f, -height * 0.5f, width * 0.5f, height * 0.5f));

	Matrix3x2F transform = m_worldMatrix;
	transform._31 += tex->GetOriginX();
	transform._32 += tex->GetOriginY();

	m_collider->Update(&transform);

	m_isDrawBoundingBox = true;
}

void Character::SetAnimation(const string& animationName)
{
	for (auto& object : m_hierarchyList)
		reinterpret_cast<Character*>(object)->m_animation = animationName;
}
